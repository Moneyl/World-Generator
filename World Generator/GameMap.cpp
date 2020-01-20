#include "GameMap.h"

const FastNoise::NoiseType TotalNoise =                   FastNoise::SimplexFractal;
const FastNoise::NoiseType HeightMapNoiseType =           TotalNoise;
const FastNoise::NoiseType HeightMapTurbulenceNoiseType = TotalNoise;
const FastNoise::NoiseType RainfallNoiseType =            TotalNoise;
const FastNoise::NoiseType TemperatureNoiseType =         TotalNoise;

void MapSystem::GameMap::GenerateHeightMap()
{
    SetWorldTileCoordinates();

    std::cout << "\n\nStarting Basic Map Generation...   ";

    sf::Clock FunctionTime;
    FunctionTime.restart();

    if(SeedType == 0)
    {
        Seed = (int)time(NULL);
    }
    else if(SeedType != 0)
    {
        Seed = SeedType;
    }

	FastNoise HeightMapNoise1;
	HeightMapNoise1.SetSeed(time(NULL));
	HeightMapNoise1.SetNoiseType(HeightMapNoiseType);
	HeightMapNoise1.SetFractalOctaves(octaves);
	HeightMapNoise1.SetFractalLacunarity(persistence);
	HeightMapNoise1.SetFractalGain(scale);
    HeightMapNoise1.SetFrequency(NoiseFrequency);

    for(int i = 0; i < MapSize; i++)
    {
		float NewHeight = HeightMapNoise1.GetNoise((float)data[i].x, (float)data[i].y);
		NewHeight += 1.0f; //Add 1.0f to make the minimum 0.0f instead of -1.0f
		NewHeight *= 127.5f; //Multiply by 127.5f to make maximum 255.0f
		data[i].z = (int)NewHeight;
    }

    if(SeedModifier < 1.0f)
    {
        SeedModifier += .01f;
    }
    if(SeedModifier >= 1.0f)
    {
        SeedModifier = .01f;
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::Turbulence()
{
	FastNoise TurbulenceNoise1;
	TurbulenceNoise1.SetNoiseType(HeightMapTurbulenceNoiseType);
	TurbulenceNoise1.SetFractalOctaves(7);
	TurbulenceNoise1.SetFractalLacunarity(2.0f);
	TurbulenceNoise1.SetFractalGain(0.5f);
    TurbulenceNoise1.SetFrequency(NoiseFrequency * 1.4f);

    for(int i = 0; i < MapSize; i++)
    {
		float NewHeight = TurbulenceNoise1.GetNoise((float)data[i].x, (float)data[i].y);
		NewHeight += 1.0f; //Add 1.0f to make the minimum 0.0f instead of -1.0f
		NewHeight *= 127.5f; //Multiply by 127.5f to make maximum 255.0f

        if(data[i].z > SeaLevel)
        {
            if(data[i].z + (NewHeight / MountainRate1) < 235 && data[i].z > SeaLevel)
            {
                data[i].z += (int)(NewHeight / MountainRate2);
            }
            else if(data[i].z + (NewHeight / 4) > 255)
            {
                data[i].z = 255;
            }
            if(data[i].z > SeaLevel && data[i].z < MountainLevel)
            {
                data[i].z -= (int)LandDecreaseLevel;
            }
            if(data[i].z >= MountainLevel)
            {
                data[i].z -= (int)MountainDecreaseLevel;
            }
        }
    }
}

int MapSystem::GameMap::ConvertToAbsolute(int xpos, int ypos)
{
    return ((ypos * x) + xpos);
}

void MapSystem::GameMap::SetSlopeValues()
{
    for(int i = 0; i < (x * y) - 1; i++)
    {
        int CurrentHeight = data[i].z;
        int Left = data[i].Left();
        int Right = data[i].Right();

        int LeftHeight;
        int RightHeight;

        if(Left > -1)
        {
            LeftHeight = data[data[i].Left()].z;
        }
        if(Right > -1)
        {
            RightHeight = data[data[i].Right()].z;
        }

        if(Right > - 1 && Left > -1)
        {
            data[i].Slope = abs(data[Right].z - data[Left].z);
        }
        if(Right <= -1 && Left > -1)
        {
            data[i].Slope = abs(data[Left].z - CurrentHeight);
        }
        if(Right > -1 && Left <= -1)
        {
            data[i].Slope = abs(data[Right].z - CurrentHeight);
        }
    }
}

void MapSystem::GameMap::SetTileBiomes()
{
    //0 = nothing
    //1 = tundra
    //2 = snow
    //3 = desert
    //4 = grassland
    //5 = decidous forest
    //6 = marshland / swamp
    //7 = tropical deciduous
    //8 = tropical rainforest
    //9 = bare
    //10 = scorched
    //11 = water
    //12 = taiga
    //13 = ice
    //14 = Savannah

    SetSlopeValues();

    for(int i = 0; i < MapSize; i++)
    {
        if(data[i].z > SeaLevel)
        {
            if(data[i].z > SeaLevel && data[i].z < MountainLevel)
            {
                if(data[i].temperature >= 0 && data[i].temperature < 108)
                {
                    if(data[i].rainfall >= 0 && data[i].rainfall < 70)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 70 && data[i].rainfall < 150)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 150 && data[i].rainfall <= 255)
                    {
                        data[i].Biome = 2;
                    }
                }
                else if(data[i].temperature >= 108 && data[i].temperature < 200)
                {
                    if(data[i].rainfall >= 0 && data[i].rainfall < 70)
                    {
                        data[i].Biome = 3;
                    }
                    else if(data[i].rainfall >= 70 && data[i].rainfall < 150)
                    {
                        data[i].Biome = 4;
                    }
                    else if(data[i].rainfall >= 150 && data[i].rainfall <= 255)
                    {
                        data[i].Biome = 5;
                    }
                }
                else if(data[i].temperature >= 200 && data[i].temperature <= 255)
                {
                    if(data[i].rainfall >= 0 && data[i].rainfall < 70)
                    {
                        data[i].Biome = 3;
                    }
                    else if(data[i].rainfall >= 70 && data[i].rainfall < 180)
                    {
                        data[i].Biome = 14;
                    }
                    else if(data[i].rainfall >= 180 && data[i].rainfall <= 255)
                    {
                        data[i].Biome = 8;
                    }
                }
            }
            else if(data[i].z >= MountainLevel && data[i].z <= 255)
            {
                if(data[i].temperature >= 0 && data[i].temperature < 108)
                {
                    data[i].Biome = 2;
                }
                else if(data[i].temperature >= 108 && data[i].temperature < 200)
                {
                    if(data[i].rainfall >= 0 && data[i].rainfall < 70)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 70 && data[i].rainfall < 150)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 150 && data[i].rainfall <= 255)
                    {
                        data[i].Biome = 2;
                    }
                }
                else if(data[i].temperature >= 200 && data[i].temperature <= 255)
                {
                    if(data[i].rainfall >= 0 && data[i].rainfall < 70)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 70 && data[i].rainfall < 150)
                    {
                        data[i].Biome = 2;
                    }
                    else if(data[i].rainfall >= 150 && data[i].rainfall <= 255)
                    {
                        data[i].Biome = 2;
                    }
                }

                if(data[i].z >= MountainLevel && data[i].z < SnowLevel)
                {
                    data[i].Biome = 9;
                }


            }
        }
        else if(data[i].z <= SeaLevel)
        {
            if(data[i].temperature >= 108)
            {
                data[i].Biome = 11;
            }
            else if(data[i].temperature < 108)
            {
                data[i].Biome = 11;
            }
        }
    }
}

void MapSystem::GameMap::FlattenIsolatedWater()//IMPROVE, DO BETTER THAN JUST ADDING TEN. PERHAPS RANDOM VALUES.
{
    for(int i = 0; i < MapSize; i++)
    {
        if(IsIsolatedWater(i) == 1)
        {
            data[i].z = SeaLevel + 10;
        }
    }
}

bool MapSystem::GameMap::InBounds(int XPos, int YPos)
{
    if(XPos > x - 1 || XPos < 0)
    {
        return 0;//EXCEPTIONS
    }
    if(YPos > y - 1 || YPos < 0)
    {
        return 0;//EXCEPTIONS
    }
    return 1;
}

bool MapSystem::GameMap::InBounds(int Position)
{
    if(Position < 0)
    {
        return 0;//EXCEPTIONS
    }
    else if(Position > (x * y) - 1)
    {
        return 0;//EXCEPTIONS
    }
    else
    {
        return 1;
    }
}

int MapSystem::GameMap::SetBaseWindRainfall(int Position) //Todo: Replace error codes with a better method of error reporting and have this return floats.
{
    if(InBounds(Position))
    {
        if(data[Position].z <= SeaLevel)
        {
            return (int)PostWaterWindRainfall;
        }
        else if(data[Position].z > SeaLevel)
        {
            if(data[Position].z < MountainLevel)
            {
                return (int)BaseWindRainfall;
            }
            else if(data[Position].z >= MountainLevel)
            {
                return (int)PostMountainWindRainfall;
            }
        }
    }
    if(!InBounds(Position))
    {
        return -1;//EXCEPTIONS
    }

}


void MapSystem::GameMap::CalculateRainShadow(bool DebugMessages)
{
char FileName[] = "";//C:/Users/moneyl/Desktop/RainShadow_Output.txt";
    std::ofstream fout(FileName);


    if(DebugMessages)
    {
        fout << "\n\n~~~BEGINNING_OF_ENTRY~~~";
    }

    int GridX = 0;
    int GridY = 0;

    int XLimit = x - 1;
    int YLimit = y - 1;

    int Position;

    bool ExitLoop = 0;

    float CurrentRainfall = 0.0f;

    std::cout << "\n\nStarting Rain shadow Calculations...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    while(ExitLoop == 0)
    {
        Position = ConvertToAbsolute(GridX, GridY);

        //fout << "\n\n IN_Y_LOOP x: " << data[Position].x << " y: " << data[Position].y << " z: " << data[Position].z;

        if(data[Position].z > SeaLevel) //Not water, go ahead.
        {
            if(data[Position].z < MountainLevel) //Not Mountain, go ahead.
            {
                if(CurrentRainfall == BaseWindRainfall) //Not desert, go here.
                {
                    //fout << "\n\nRainfall not desert level, Current Rainfall: " << CurrentRainfall;

                    data[Position].rainfall = CurrentRainfall;

                    //fout << "\n\n Current Position Rainfall: " << data[Position].rainfall;
                }

                else if(CurrentRainfall < BaseWindRainfall) //Desert, go here.
                {
                    //fout << "\n\nRainfall at desert level, Current Rainfall: " << CurrentRainfall;

                    data[Position].rainfall = CurrentRainfall;
                    CurrentRainfall += RainfallIncreaseDelta;
                    //fout << " Rainfall after change: " << CurrentRainfall;

                    //fout << "\n\n Current Position Rainfall: " << data[Position].rainfall;
                }

                else if(CurrentRainfall > BaseWindRainfall)
                {
                    if(CurrentRainfall - RainfallDecreaseDelta < BaseWindRainfall)
                    {
                        data[Position].rainfall = CurrentRainfall;
                        CurrentRainfall = BaseWindRainfall;
                    }

                    else if(CurrentRainfall - RainfallDecreaseDelta >= BaseWindRainfall)
                    {
                        data[Position].rainfall = CurrentRainfall;
                        CurrentRainfall -= RainfallDecreaseDelta;
                    }
                }
            }

            else if(data[Position].z >= MountainLevel) //Mountain, go here.
            {
                //fout << "\n\nHit Mountain! Current Rainfall: " << CurrentRainfall;

                if(CurrentRainfall - (RainfallDecreaseDelta * RainfallMultiplier) >= 0)
                {
                    CurrentRainfall -= RainfallDecreaseDelta * 4;
                }
                else if(CurrentRainfall - (RainfallDecreaseDelta * RainfallMultiplier) < 0)
                {
                    CurrentRainfall = 0;
                }
                data[Position].rainfall = CurrentRainfall;

                //fout << " Rainfall after change: " << CurrentRainfall;
                //fout << "\n\n Current Position Rainfall: " << data[Position].rainfall;

            }
        }

        else if(data[Position].z <= SeaLevel) //Water, go here.
        {
            //fout << "\n\nHit Water! CurrentRainfall: " << CurrentRainfall;

            data[Position].rainfall = 182;

            if(CurrentRainfall + (RainfallDecreaseDelta * RainfallMultiplier) <= 255)
            {
                CurrentRainfall += RainfallDecreaseDelta * 4;
            }
            else if(CurrentRainfall - (RainfallDecreaseDelta * RainfallMultiplier) > 255)
            {
                CurrentRainfall = 255;
            }


            //fout << " Rainfall after change: " << CurrentRainfall;
            //fout << "\n\n Current Position Rainfall: " << data[Position].rainfall;

        }

        if(GridY < YLimit && GridX == XLimit)
        {
            CurrentRainfall = BaseWindRainfall;
            GridX = 0;
            GridY++;
        }
        else if(GridX < XLimit)
        {
            GridX++;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {
            ExitLoop = 1; //Exit condition.
        }
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout << FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::IncrementModifiers()
{
    if(ModifierOne < ModOneMax)
    {
        ModifierOne += ModOneAdd;
    }
    else if(FloatAlmostEqual(ModifierOne, ModOneMax))
    {
        ModifierOne = 0.01f;
    }

    if(ModifierTwo < ModTwoMax)
    {
        ModifierTwo += ModTwoAdd;
    }
    else if(FloatAlmostEqual(ModifierTwo, ModTwoMax))
    {
        ModifierTwo = 0.0001f;
    }
}

int MapSystem::GameMap::GetChannelHeight()
{
    srand((unsigned int)time(NULL));
    int ChannelWidth = 0;

    while(ChannelWidth < MinimumChannelHeight)
    {
        ChannelWidth = static_cast<int>(rand() * ModifierOne * ModifierTwo) % MaximumChannelHeight;
        IncrementModifiers();
    }
    return ChannelWidth;
}

bool MapSystem::GameMap::InvalidAngle(int Angle)
{
    for(int i = 0; i < ChannelLocations.size(); i++)
    {
        if(data[ConvertToAbsolute(0, ChannelLocations[i])].WindAngle == Angle)
        {
            return 1;
        }
    }
    if(Angle == -1)
    {
        return 1;
    }
    return 0;
}

void MapSystem::GameMap::SetWindAngles()
{
    srand((unsigned int)time(NULL));
    int CurrentAngle = -1;
    int CurrentRow = 0; //Current Y-Value.
    int ChannelHeight;

    while(CurrentRow <= y - 1)//Check this less than, might need to change...
    {
        ChannelHeight = GetChannelHeight();
        ChannelLocations.push_back(CurrentRow);
        if(CurrentRow + ChannelHeight <= y - 1)
        {
            IncrementModifiers();

            while(InvalidAngle(CurrentAngle))
            {
                CurrentAngle = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand() * rand()) % MaximumAngle;
            }

            for(int i = ConvertToAbsolute(0, CurrentRow); i <= ConvertToAbsolute(x - 1, CurrentRow + ChannelHeight); i++)
            {
                data[i].WindAngle = CurrentAngle;
            }
            CurrentRow += ChannelHeight;
        }
        else if(CurrentRow + ChannelHeight > y - 1)
        {
            IncrementModifiers();
            ChannelHeight = (y - 1) - CurrentRow;

            while(InvalidAngle(CurrentAngle))
            {
                CurrentAngle = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand() * rand()) % MaximumAngle;
            }

            for(int i = ConvertToAbsolute(0, CurrentRow); i <= ConvertToAbsolute(x - 1, CurrentRow + ChannelHeight); i++)
            {
                data[i].WindAngle = CurrentAngle;
            }
            CurrentRow = y;
        }

    }
}

void MapSystem::GameMap::ApplyNoiseToWindAngles()
{
    /*for(int i = 0; i < (x * y) - 1; i++)
    {
        int Noise = static_cast<int>(rand() * scaled_octave_noise_3d(15.0f, 
			0.99f, 0.005f, 1.0f, 0.0f, (float)MaximumNoiseAngle, 
			(float)data[i].y, (float)data[i].z, 
			(float)data[i].x)) % MaximumNoiseAngle;

        data[i].WindAngle += Noise;
    }*/
}

void MapSystem::GameMap::CalculateMapRainfall(bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/Rainfall_Calc_Output.txt";
    std::ofstream fout(FileName);

    if(DebugMessages)
    {
        fout << "\n\n~~~BEGINNING_OF_ENTRY~~~";
    }

    int GridX = 0;
    int GridY = 0;

    int XLimit = x - 1;
    int YLimit = y - 1;

    int TempArrayPos;

    std::cout << "\n\nStarting Rainfall Calculations...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();


    while(GridY <= YLimit && GridX <= XLimit)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);
        if(DebugMessages)
        {
            fout << "\n\n" << "x: " << data[TempArrayPos].x << " y: " << data[TempArrayPos].y << " z:" << data[TempArrayPos].z;
        }

        if(data[TempArrayPos].z <= SeaLevel)
        {
            if(DebugMessages)
            {
                fout << "\n HIT WATER!";
            }

            if(IsDeepOcean(ConvertToAbsolute(GridX, GridY)) == 0)
            {
                if(DebugMessages)
                {
                    fout << "\nIsDeepOcean: " << IsDeepOcean(ConvertToAbsolute(GridX, GridY));
                }

                int GridX2 = GridX + 1;
                int GridY2 = GridY;

                int TempArrayPos2;

                float BaseRainfall = 180.0;
                float RainfallChange;

                bool ExitLoop = 0;
                if(GridX + 1 <= XLimit)
                {
                    do//right/east
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);
                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nRIGHT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 + 1 <= XLimit)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2++;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 + 1 > XLimit)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 <= XLimit)
                        {
                            GridX2++;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 > XLimit)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX - 1;
                GridY2 = GridY;

                BaseRainfall = 255.0;

                ExitLoop = 0;

                if(GridX - 1 >= 0)
                {
                    do//left/west
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                        else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nLEFT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 - 1 >= 0)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2--;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 - 1 < 0)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 >= 0)
                        {
                            GridX2--;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 < 0)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX;
                GridY2 = GridY - 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridY - 1 >= 0)
                {
                    do//up/north
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                       else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                               data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nUP GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridY2 - 1 >= 0)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridY2--;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridY2 - 1 < 0)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridY2 - 1 >= 0)
                        {
                            GridY2--;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridY2 - 1 < 0)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX;
                GridY2 = GridY + 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridY + 1 <= YLimit)
                {
                    do//down/south
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                      else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                              data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nDOWN GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridY2 + 1 <= YLimit)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridY2++;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridY2 + 1 > YLimit)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridY2 + 1 <= YLimit)
                        {
                            GridY2++;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridY2 + 1 > YLimit)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX - 1;
                GridY2 = GridY - 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridX - 1 >= 0 && GridY - 1 >= 0)
                {
                    do//upperleft/northwest
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                       else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                               data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nUPLEFT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 - 1 >= 0 && GridY2 - 1 >= 0)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2--;
                                GridY2--;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 - 1 < 0 || GridY2 -1 < 0)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 >= 0 &&  GridY2 - 1 >= 0)
                        {
                            GridX2--;
                            GridY2--;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 < 0 && GridY2 - 1 < 0)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX + 1;
                GridY2 = GridY - 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridX + 1 <= XLimit && GridY - 1 >= 0)
                {
                    do//upperright/northeast
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                       else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                               data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nUPRIGHT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 + 1 <= XLimit && GridY2 - 1 >= 0)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2++;
                                GridY2--;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 + 1 > XLimit || GridY2 - 1 < 0)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 <= XLimit && GridY2 - 1 >= 0)
                        {
                            GridX2++;
                            GridY2--;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 > XLimit && GridY2 - 1 < 0)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX - 1;
                GridY2 = GridY + 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridX - 1 >= 0 && GridY + 1 <= YLimit)
                {
                    do//lowerleft/southwest
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                 else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                            data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nDOWNLEFT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 - 1 >= 0 && GridY2 + 1 <= YLimit)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2--;
                                GridY2++;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 - 1 < 0 || GridY2 + 1 > YLimit)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 >= 0 && GridY2 + 1 <= YLimit)
                        {
                            GridX2--;
                            GridY2++;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 - 1 < 0 && GridY2 + 1 > YLimit)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }

                GridX2 = GridX + 1;
                GridY2 = GridY + 1;

                BaseRainfall = 255.0;

                ExitLoop = 0;
                if(GridX + 1 <= XLimit && GridY + 1 <= YLimit)
                {
                    do//lowerright/southeast
                    {
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z > SeaLevel)
                        {
                            TempArrayPos2 = ConvertToAbsolute(GridX2, GridY2);

                            if(data[TempArrayPos2].rainfall < RainfallOverlapValue)
                            {
                                data[TempArrayPos2].rainfall = BaseRainfall;
                            }
                            else if(data[TempArrayPos2].rainfall >= RainfallOverlapValue)
                            {
                                if(data[TempArrayPos2].rainfall < PostWaterWindRainfall)
                                {
                                    float TempDivisorLevel = BaseRainfall / data[TempArrayPos2].rainfall;
                                    if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) <= 255)
                                    {
                                        data[TempArrayPos2].rainfall += BaseRainfall / TempDivisorLevel;
                                    }
                                    else if(data[TempArrayPos2].rainfall + (BaseRainfall / TempDivisorLevel) > 255)
                                    {
                                        data[TempArrayPos2].rainfall = 255;
                                    }
                                }
                            }
                            /*                      else if(data[TempArrayPos2].rainfall <= RainfallOverlapValue)
                            {
                              data[TempArrayPos2].rainfall += BaseRainfall * RainfallOverlapMultiplier;
                            }*/

                            RainfallChange = data[TempArrayPos2].z / RainfallDivisor;
                            if(DebugMessages)
                            {
                                fout << "\n\nDOWNRIGHT GridX2: " << GridX2 << " GridY2: " << GridY2 << " BaseRainfall: " << BaseRainfall;
                            }

                            if(BaseRainfall - RainfallChange >= 0 && GridX2 + 1 <= XLimit && GridY2 + 1 <= YLimit)
                            {
                                //HeightVariation = data[TempArrayPos2].z / RainfallDivisor;
                                //fout << " HeightVariation: " << HeightVariation;

                                if(DebugMessages)
                                {
                                    fout << " RainfallChange: " << RainfallChange;
                                }
                                BaseRainfall -= RainfallChange;
                                if(DebugMessages)
                                {
                                    fout << " BaseRainfallAfterChange: " << BaseRainfall;
                                }

                                GridX2++;
                                GridY2++;
                            }
                            else if(BaseRainfall - RainfallChange < 0 || GridX2 + 1 > XLimit || GridY2 + 1 > YLimit)
                            {
                                ExitLoop = 1;
                            }
                        }
                        if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 <= XLimit && GridY2 + 1 <= YLimit)
                        {
                            GridX2++;
                            GridY2++;
                        }
                        else if(data[ConvertToAbsolute(GridX2, GridY2)].z <= SeaLevel && GridX2 + 1 > XLimit && GridY2 + 1 > YLimit)
                        {
                            ExitLoop = 1;
                        }
                    }
                    while(ExitLoop == 0);
                }


                //std::cout << "\n \n" << "x: " << data[TempArrayPos].x << " y: " << data[TempArrayPos].y << " z:" << data[TempArrayPos].z;
            }
        }

        if(GridY < YLimit && GridX <= XLimit)
        {
            GridY++;
        }

        else if(GridY == YLimit && GridX < XLimit)
        {
            GridY = 0;
            GridX++;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {
            fout << "\n\n~~~END_OF_ENTRY~~~";
            fout.close();
            GridX = XLimit + 1; //Exit condition.
            if(DebugMessages)
            {
                fout << "\n\n~~~END_OF_ENTRY~~~";
            }
        }
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout << FunctionSeconds.asSeconds() << " Seconds.";
}

bool MapSystem::GameMap::IsDeepOcean(int Position)
{
    if(data[Position].z <= SeaLevel)
    {
        int Left;
        int Right;
        int Above;
        int Below;
        int UpperLeft;
        int UpperRight;
        int LowerLeft;
        int LowerRight;

        if(data[Position].Left() > -1)
        {
            Left = data[data[Position].Left()].z;
        }
        if(data[Position].Right() > -1)
        {
            Right = data[data[Position].Right()].z;
        }
        if(data[Position].Above() > -1)
        {
            Above = data[data[Position].Above()].z;
        }
        if(data[Position].Below() > -1)
        {
            Below = data[data[Position].Below()].z;
        }
        if(data[Position].UpperLeft() > -1)
        {
            UpperLeft = data[data[Position].UpperLeft()].z;
        }
        if(data[Position].UpperRight() > -1)
        {
            UpperRight = data[data[Position].UpperRight()].z;
        }
        if(data[Position].LowerLeft() > -1)
        {
            LowerLeft = data[data[Position].LowerLeft()].z;
        }
        if(data[Position].LowerRight() > -1)
        {
            LowerRight = data[data[Position].LowerRight()].z;
        }

        if(Left <= SeaLevel && Right <= SeaLevel && Above <= SeaLevel && Below <= SeaLevel && UpperLeft <= SeaLevel && UpperRight <= SeaLevel && LowerLeft <= SeaLevel && LowerRight <= SeaLevel)
        {
            return 1;
        }
    }
    return 0;
}

bool MapSystem::GameMap::IsDeepMountain(int Position)
{
    if(data[Position].z >= MountainLevel)
    {
        int Left = 0;
        int Right = 0;
        int Above = 0;
        int Below = 0;
        int UpperLeft = 0;
        int UpperRight = 0;
        int LowerLeft = 0;
        int LowerRight = 0;

        if(data[Position].Left() > -1)
        {
            Left = data[data[Position].Left()].z;
        }
        if(data[Position].Right() > -1)
        {
            Right = data[data[Position].Right()].z;
        }
        if(data[Position].Above() > -1)
        {
            Above = data[data[Position].Above()].z;
        }
        if(data[Position].Below() > -1)
        {
            Below = data[data[Position].Below()].z;
        }
        if(data[Position].UpperLeft() > -1)
        {
            UpperLeft = data[data[Position].UpperLeft()].z;
        }
        if(data[Position].UpperRight() > -1)
        {
            UpperRight = data[data[Position].UpperRight()].z;
        }
        if(data[Position].LowerLeft() > -1)
        {
            LowerLeft = data[data[Position].LowerLeft()].z;
        }
        if(data[Position].LowerRight() > -1)
        {
            LowerRight = data[data[Position].LowerRight()].z;
        }

		//Todo: Try to improve the logic here. If MountainLevel == 0, then it will fail.
        if(Left >= MountainLevel && Right >= MountainLevel && Above >= MountainLevel && Below >= MountainLevel && UpperLeft >= MountainLevel && UpperRight >= MountainLevel && LowerLeft >= MountainLevel && LowerRight >= MountainLevel)
        {
            return true;
        }
    }
    return true;
}

bool MapSystem::GameMap::IsBiomeBorder(int Position)
{
    int LeftBiome = 1;
    int RightBiome = 1;
    int AboveBiome = 1;
    int BelowBiome = 1;
    int UpperLeftBiome = 1;
    int UpperRightBiome = 1;
    int LowerLeftBiome = 1;
    int LowerRightBiome = 1;

    int PositionBiome = data[Position].Biome;

    //Different Biome = 0.
    //Same Biome = 1.

    if(data[Position].Left() > -1)
    {
        if(data[data[Position].Left()].Biome != PositionBiome)
        {
            LeftBiome = 0;
        }
    }
    if(data[Position].Right() > -1)
    {
        if(data[data[Position].Right()].Biome != PositionBiome)
        {
            RightBiome = 0;
        }
    }
    if(data[Position].Above() > -1)
    {
        if(data[data[Position].Above()].Biome != PositionBiome)
        {
            AboveBiome = 0;
        }
    }
    if(data[Position].Below() > -1)
    {
        if(data[data[Position].Below()].Biome != PositionBiome)
        {
            BelowBiome = 0;
        }
    }
    if(data[Position].UpperLeft() > -1)
    {
        if(data[data[Position].UpperLeft()].Biome != PositionBiome)
        {
            UpperLeftBiome = 0;
        }
    }
    if(data[Position].UpperRight() > -1)
    {
        if(data[data[Position].UpperRight()].Biome != PositionBiome)
        {
            UpperRightBiome = 0;
        }
    }
    if(data[Position].LowerLeft() > -1)
    {
        if(data[data[Position].LowerLeft()].Biome != PositionBiome)
        {
            LowerLeftBiome = 0;
        }
    }
    if(data[Position].LowerRight() > -1)
    {
        if(data[data[Position].LowerRight()].Biome != PositionBiome)
        {
            LowerRightBiome = 0;
        }
    }

    if(LeftBiome + RightBiome + AboveBiome + BelowBiome + UpperLeftBiome + UpperRightBiome + LowerLeftBiome + LowerRightBiome < 8)
    {
        return true;
    }
    else if(LeftBiome == 1 && RightBiome == 1 && AboveBiome == 1 && BelowBiome == 1 && UpperLeftBiome == 1 && UpperRightBiome == 1 && LowerLeftBiome == 1 && LowerRightBiome == 1)
    {
        return false;
    }
	return false;
}

bool MapSystem::GameMap::IsIsolatedWater(int Position)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/IsIsolatedWater.txt";
    std::ofstream fout(FileName, std::ios::app);
    if(data[Position].z <= SeaLevel)
    {
        int aLeft = data[Position].Left();
        int aRight = data[Position].Right();
        int aAbove = data[Position].Above();
        int aBelow = data[Position].Below();
        int aUpperLeft = data[Position].UpperLeft();
        int aUpperRight = data[Position].UpperRight();
        int aLowerLeft = data[Position].LowerLeft();
        int aLowerRight = data[Position].LowerRight();

        int Left2;
        int Right2;
        int Above2;
        int Below2;
        int UpperLeft2;
        int UpperRight2;
        int LowerLeft2;
        int LowerRight2;

        if(aLeft > -1)
        {
            Left2 = data[aLeft].z;
        }
        else if(aLeft <= -1)
        {
            Left2 = SeaLevel + 1;
        }
        if(aRight > -1)
        {
            Right2 = data[aRight].z;
        }
        else if(aRight <= -1)
        {
            Right2 = SeaLevel + 1;
        }
        if(aAbove > -1)
        {
            Above2 = data[aAbove].z;
        }
        else if(aAbove <= -1)
        {
            Above2 = SeaLevel + 1;
        }
        if(aBelow > -1)
        {
            Below2 = data[aBelow].z;
        }
        else if(aBelow <= -1)
        {
            Below2 = SeaLevel + 1;
        }
        if(aUpperLeft > -1)
        {
            UpperLeft2 = data[aUpperLeft].z;
        }
        else if(aUpperLeft <= -1)
        {
            UpperLeft2 = SeaLevel + 1;
        }
        if(aUpperRight > -1)
        {
            UpperRight2 = data[aUpperRight].z;
        }
        else if(aUpperRight <= -1)
        {
            UpperRight2 = SeaLevel + 1;
        }
        if(aLowerLeft > -1)
        {
            LowerLeft2 = data[aLowerLeft].z;
        }
        else if(aLowerLeft <= -1)
        {
            LowerLeft2 = SeaLevel + 1;
        }
        if(aLowerRight > -1)
        {
            LowerRight2 = data[aLowerRight].z;
        }
        else if(aLowerRight <= -1)
        {
            LowerRight2 = SeaLevel + 1;
        }

        if(Left2 > SeaLevel && Right2 > SeaLevel && Above2 > SeaLevel && Below2 > SeaLevel && UpperLeft2 > SeaLevel && UpperRight2 > SeaLevel && LowerLeft2 > SeaLevel && LowerRight2 > SeaLevel)
        {
            //fout << "\nIsIsolatedWater: 1";
            return 1;
        }
    }
    //fout << "\nIsIsolatedWater: 0";
    return 0;
}

void MapSystem::GameMap::GenerateTemperatureMap()
{
    //TemperatureDivisor = y / TemperatureDivisor;
    for(int i = 0; i < x * y - 1; i++)
    {
        if(data[i].y <= y / 2)
        {
            int TempY = data[i].y;
            data[i].temperature = (float)((TemperatureMultiplier * pow(TempY, 2)) + (1 * TempY) + 1) / TemperatureDivisor;
        }
        else
        {
            int TempY = y - data[i].y;
            data[i].temperature = (float)((TemperatureMultiplier * pow(TempY, 2)) + (1 * TempY) + 1) / TemperatureDivisor;
        }
        if(data[i].temperature > 255)
        {
            data[i].temperature = 255;
        }
        if(data[i].temperature < 0)
        {
            data[i].temperature = 0;
        }
    }
}

void MapSystem::GameMap::ApplyNoiseToRainfall()
{
	FastNoise RainfallNoise1;
	RainfallNoise1.SetNoiseType(RainfallNoiseType);
	RainfallNoise1.SetFractalOctaves(1.0f);
	RainfallNoise1.SetFractalLacunarity(0.9f);
	RainfallNoise1.SetFractalGain(0.1f);
    for(int i = 0; i < MapSize; i++)
    {
		float NewRainfall = RainfallNoise1.GetNoise((float)data[i].x, (float)data[i].y);
		NewRainfall += 1.0f; //Add 1.0f to make the minimum 0.0f instead of -1.0f
		NewRainfall *= 127.5f; //Multiply by 127.5f to make maximum 255.0f
		NewRainfall = (NewRainfall + data[i].rainfall) / 2.0f;

        if(data[i].rainfall < 70)
        {
            if(data[i].rainfall + (NewRainfall / 4) <= 255)
            {
                data[i].rainfall += (NewRainfall / 4);
            }
            else if(data[i].rainfall + (NewRainfall / 4) > 255)
            {
                data[i].rainfall = 255;
            }
        }
        else if(data[i].rainfall >= 180)
        {
            if(data[i].rainfall - (NewRainfall / 4) >= 0)
            {
                data[i].rainfall -= (NewRainfall / 4);
            }
            else if(data[i].rainfall - (NewRainfall / 4) < 0)
            {
                data[i].rainfall = 0;
            }
        }

        /*if(data[i].rainfall + (NewRainfall / 4) < 255 && data[i].rainfall + (NewRainfall / 4) < RainfallNoiseThreshold)
        {
            data[i].rainfall += NewRainfall / 4;
        }
        else if(data[i].rainfall + (NewRainfall / 8) > 255)
        {
            data[i].rainfall = 255;
        }*/
    }
}

void MapSystem::GameMap::SmoothRainfall()
{
    for(int i = 0; i < MapSize; i++)
    {
        if(data[i].IsCorner() > 0)
        {
            if(data[i].IsCorner() == 1)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Right()].rainfall + data[data[i].LowerRight()].rainfall + data[data[i].Below()].rainfall) / 4;
            }
            else if(data[i].IsCorner() == 2)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Left()].rainfall + data[data[i].LowerLeft()].rainfall + data[data[i].Below()].rainfall) / 4;
            }
            else if(data[i].IsCorner() == 3)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Left()].rainfall + data[data[i].UpperLeft()].rainfall + data[data[i].Above()].rainfall) / 4;
            }
            else if(data[i].IsCorner() == 4)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Right()].rainfall + data[data[i].UpperRight()].rainfall + data[data[i].Above()].rainfall) / 4;
            }
        }
        else if(data[i].IsSide() > 0)
        {
            if(data[i].IsSide() == 1)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Right()].rainfall + data[data[i].LowerRight()].rainfall + data[data[i].Below()].rainfall + data[data[i].LowerLeft()].rainfall + data[data[i].Left()].rainfall) / 6;
            }
            if(data[i].IsSide() == 2)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Above()].rainfall + data[data[i].UpperLeft()].rainfall + data[data[i].Left()].rainfall + data[data[i].LowerLeft()].rainfall + data[data[i].Below()].rainfall) / 6;
            }
            if(data[i].IsSide() == 3)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Left()].rainfall + data[data[i].UpperLeft()].rainfall + data[data[i].Above()].rainfall + data[data[i].UpperRight()].rainfall + data[data[i].Right()].rainfall) / 6;
            }
            if(data[i].IsSide() == 4)
            {
                data[i].rainfall = (data[i].rainfall + data[data[i].Above()].rainfall + data[data[i].UpperRight()].rainfall + data[data[i].Right()].rainfall + data[data[i].LowerRight()].rainfall + data[data[i].Below()].rainfall) / 6;
            }
        }
        else if(!data[i].IsBorderTile())
        {
            data[i].rainfall = (data[i].rainfall + data[data[i].Left()].rainfall + data[data[i].UpperLeft()].rainfall + data[data[i].Above()].rainfall + data[data[i].UpperRight()].rainfall + data[data[i].Right()].rainfall + data[data[i].LowerRight()].rainfall + data[data[i].Below()].rainfall + data[data[i].LowerLeft()].rainfall) / 9;
        }
    }
}

void MapSystem::GameMap::ApplyNoiseToTemperature()//Observe differences between this and rainfall noise to improve noise for both
{
	FastNoise TemperatureNoise1;
	TemperatureNoise1.SetNoiseType(TemperatureNoiseType);
	TemperatureNoise1.SetFractalOctaves(7.0f);
	TemperatureNoise1.SetFractalLacunarity(0.5f);
	TemperatureNoise1.SetFractalGain(0.1f);
    for(int i = 0; i < MapSize; i++)
    {
        int seed2 = (int)time(NULL);
        srand(seed2);
		
		float NewTemperature = TemperatureNoise1.GetNoise((float)data[i].x, (float)data[i].y);
		NewTemperature += 1.0f; //Add 1.0f to make the minimum 0.0f instead of -1.0f
		NewTemperature *= 127.5f; //Multiply by 127.5f to make maximum 255.0f
		NewTemperature = (NewTemperature + data[i].rainfall) / 2.0f;

        if(data[i].temperature + (NewTemperature / 4) < 255)
        {
            data[i].temperature += NewTemperature / 4;
        }
        else if(data[i].temperature + (NewTemperature / 8) > 255)
        {
            data[i].temperature = 255;
        }
        else if(data[i].temperature + (NewTemperature / 2) > 225)
        {
            data[i].temperature -= NewTemperature / 4;
        }
    }
}

void MapSystem::GameMap::SetWorldTileCoordinates()
{
    for(int i = 0; i < MapSize; i++)
    {
        data[i].x = i % x;
        data[i].y = i / x;

        data[i].MapWidth = x;
        data[i].MapHeight = y;
    }
}

void MapSystem::GameMap::SmoothNoise(bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/Debug_Output_Smoothing.txt";
    std::ofstream fout(FileName, std::ios::app);

    if(DebugMessages)
    {
        fout << "\n\n~~~BEGINNING_OF_ENTRY~~~";
    }

    int GridX = 1;
    int GridY = 1;

    int XLimit = x - 2;
    int YLimit = y - 2;

    std::cout << "\n\nStarting Noise Smoothing...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    while(GridY <= YLimit && GridX <= XLimit)
    {
        int cvar1 = data[ConvertToAbsolute(GridX - 1, GridY - 1)].z;
        int cvar2 = data[ConvertToAbsolute(GridX + 1, GridY + 1)].z;
        int cvar3 = data[ConvertToAbsolute(GridX - 1, GridY + 1)].z;
        int cvar4 = data[ConvertToAbsolute(GridX + 1, GridY -1)].z;
        int cvar5 = cvar1 + cvar2 + cvar3 + cvar4;
        int corners = cvar5 / CornerSmoothScale;

        if(DebugMessages)
        {
            fout << "\n\nCenter x-value: " << GridX << " Center y-value: " << GridY << " Center z-value: " << data[ConvertToAbsolute(GridX, GridY)].z << " Corners Smooth Value: " << corners;
        }

        int svar1 = data[ConvertToAbsolute(GridX + 1, GridY)].z;
        int svar2 = data[ConvertToAbsolute(GridX - 1, GridY)].z;
        int svar3 = data[ConvertToAbsolute(GridX, GridY + 1)].z;
        int svar4 = data[ConvertToAbsolute(GridX, GridY - 1)].z;
        int svar5 = svar1 + svar2 + svar3 + svar4;
        int sides = svar5 / SideSmoothScale;

        if(DebugMessages)
        {
            fout << "\n\nCenter x-value: " << GridX << " Center y-value: " << GridY << " Center z-value: " << data[ConvertToAbsolute(GridX, GridY)].z << " Sides Smooth Value: " << sides;
        }

        int cevar1 = data[ConvertToAbsolute(GridX, GridY)].z;
        int center = cevar1 / 4;

        if(DebugMessages)
        {
            fout << "\n\nCenter x-value: " << GridX << " Center y-value: " << GridY << " Center z-value: " << data[ConvertToAbsolute(GridX, GridY)].z << " Center Smoothed Value: " << center;
        }

        int smoothedvar = corners + sides + center;

        if(DebugMessages)
        {
            fout << "\n\nCenter x-value: " << GridX << " Center y-value: " << GridY << " Center z-value: " << data[ConvertToAbsolute(GridX, GridY)].z << " Smoothed Z Value: " << smoothedvar;
        }

        data[ConvertToAbsolute(GridX, GridY)].z = smoothedvar;

        if(GridY < YLimit && GridX <= XLimit)
        {
            GridY++;
        }

        else if(GridY == YLimit && GridX < XLimit)
        {
            GridY = 1;
            GridX++;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {
            if(DebugMessages)
            {
                fout << "\n\n~~~END_OF_ENTRY~~~";
                fout.close();
            }
            GridX = XLimit + 1; //Exit condition.
        }

    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout << FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::InterpolateX()
{
    int GridX = 0;
    int GridY = 0;

    int XLimit = x - 1;
    int YLimit = y - 1;


    int CurrentPos = 0;

    std::cout << "\n\nStarting X Interpolating...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();


    while(GridY <= YLimit && GridX <= XLimit)
    {
        int TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX - 1, GridY)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX + 1, GridY)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        if(GridY <= YLimit && GridX < XLimit)
        {
            GridX++;
        }

        else if(GridY < YLimit && GridX == XLimit)
        {
            GridY++;
            GridX = 0;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {

            GridX = XLimit + 1; //Exit condition.
        }
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::InterpolateY()
{
    int GridX = 0;
    int GridY = 0;

    int XLimit = x - 1;
    int YLimit = y - 1;


    int CurrentPos = 0;

    std::cout << "\n\nStarting Y Interpolating...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();


    while(GridY <= YLimit && GridX <= XLimit)
    {
        int TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX - 1, GridY)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX + 1, GridY)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        if(GridY < YLimit && GridX <= XLimit)
        {
            GridY++;
        }

        else if(GridY == YLimit && GridX < XLimit)
        {
            GridY = 0;
            GridX++;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {

            GridX = XLimit + 1; //Exit condition.
        }
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::InterpolateBoth()
{
    InterpolateX();
    InterpolateY();
}

int MapSystem::GameMap::IsCorner(int cx, int cy)
{
    if(cx <= -1)
    {
        return -1;
    }
    if(cy <= -1)
    {
        return -1;
    }
    if(cx == 0 && cy == 0)
    {
        return 1; //Top left.
    }
    else if(cx == 0 && cy == y - 1)
    {
        return 2; //Bottom left.
    }
    else if(cx == x - 1 && cy == 0)
    {
        return 3; //Top right.
    }
    else if(cx == x - 1 && cy == y - 1)
    {
        return 4; //Bottom right.
    }

    else
    {
        return 0;
    }
}

int MapSystem::GameMap::IsSide(int sx, int sy)
{
    if(sx <= -1)
    {
        return -1;
    }
    if(sy <= -1)
    {
        return -1;
    }
    if(sx >= 1 && sx <= x - 2)
    {
        if(sy == 0)
        {
            return 1; //Top
        }
        else if(sy == y - 1)
        {
            return 2; //Bottom
        }
        else
        {
            return 0;
        }
    }
    else if(sy >= 1 && sy <= y - 2)
    {
        if(sx == 0)
        {
            return 3; //Left
        }
        else if(sx == x - 1)
        {
            return 4; //Right
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

bool MapSystem::GameMap::IsCenter(int cex, int cey)
{
    int tempcorner = IsCorner(cex, cey);
    int tempside = IsSide(cex, cey);

    if(tempcorner == 0 && tempside == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void MapSystem::GameMap::SmoothNoiseOutside(bool DebugMessages)
{
    int GridX = 0;
    int GridY = 0;
    int TempArrayPos;
    int XLimit = x - 1;
    int YLimit = y - 1;
    int CurrentPos = 0;

    char FileName[] = "";//C:/Users/moneyl/Desktop/OutsideSmooth.txt";
    std::ofstream fout(FileName, std::ios::app);

    if(DebugMessages)
    {
        fout << "~~~BEGINNING_OF_ENTRY~~~";
    }
    std::cout << "\n\nStarting Outside Smoothing...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    while(GridX <= XLimit)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX - 1, GridY)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX + 1, GridY)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        GridX++;
        CurrentPos++;
    }

    GridX = 0;
    GridY = y - 1;
    CurrentPos = 0;

    while(GridX <= XLimit)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX - 1, GridY)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX + 1, GridY)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        GridX++;
        CurrentPos++;
    }

    GridX = 0;
    GridY = 0;
    CurrentPos = 0;

    while(GridY <= YLimit)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX, GridY - 1)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX, GridY + 1)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        GridY++;
        CurrentPos++;
    }

    GridX = x - 1;
    GridY = 0;
    CurrentPos = 0;

    while(GridY <= YLimit)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);

        float TempFloatZX = (float)data[TempArrayPos].z;
        float var1 = TempFloatZX * 3.1415927f;
        float var2 = (1.0f - cosf(var1)) * 0.5f;
        float var3;

        if(CurrentPos > 0)
        {
            float LastZPos = (float)data[ConvertToAbsolute(GridX, GridY - 1)].z;
            float var4 = LastZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;

            data[TempArrayPos].z = static_cast<int> (var3);
        }

        else if(CurrentPos == 0)
        {
            float NextZPos = (float)data[ConvertToAbsolute(GridX, GridY + 1)].z;
            float var4 = NextZPos * (1 - var2);
            float var5 = TempFloatZX * var2;
            var3 = var4 + var5;
            data[TempArrayPos].z = static_cast<int> (var3);
        }

        GridY++;
        CurrentPos++;
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::GameMap::CalculateMapRegions(bool DebugMessages)
{
    //0 = nothing
    //1 = tundra
    //2 = snow
    //3 = desert
    //4 = grassland
    //5 = decidous forest
    //6 = marshland / swamp
    //7 = tropical deciduous
    //8 = tropical rainforest
    //9 = bare
    //10 = scorched
    //11 = water

    char FileName[] = "";//C:/Users/moneyl/Desktop/RegionDetection.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    if(DebugMessages)
    {
        fout << "~~~BEGINNING_OF_ENTRY~~~";
    }


    std::cout << "\n\nStarting Region Detection...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    int GridX = 0;
    int GridY = 0;

    int XLimit = x - 1;
    int YLimit = y - 1;

    std::queue <int> CoordinateQueue;

    bool exit = 0;

    int CurrentBiome;
    int TempArrayPos;
    int TempArrayPos2;
    int CurrentRegion = 0;

    while(exit == 0)
    {
        TempArrayPos = ConvertToAbsolute(GridX, GridY);
        bool exit2 = 0;

        if(DebugMessages)
        {
            fout << "\n\n LOOP-ONE" << " X: " << GridX << " Y: " << GridY;
        }
        if(data[TempArrayPos].InBiomeRegion == 0)
        {
            CurrentBiome = data[TempArrayPos].Biome;

            NatureRegionsContainer.push_back(NatureRegion());
            NatureRegionsContainer[CurrentRegion].Type = CurrentBiome;
            NatureRegionsContainer[CurrentRegion].RegionColor.r = 0;//-1; There may be a check for -1 someone which always fails since char >= 0
            NatureRegionsContainer[CurrentRegion].RegionColor.g = 0;//-1;
            NatureRegionsContainer[CurrentRegion].RegionColor.b = 0;//-1;

            CoordinateQueue.push(TempArrayPos);

            while(exit2 == 0)
            {
                TempArrayPos2 = CoordinateQueue.front();

                int aLeft = data[TempArrayPos2].Left();
                int aRight = data[TempArrayPos2].Right();
                int aAbove = data[TempArrayPos2].Above();
                int aBelow = data[TempArrayPos2].Below();

                if(DebugMessages)
                {
                    fout << "\n Absolute of Loop-Two: " << TempArrayPos2;
                }

                NatureRegionsContainer[CurrentRegion].AddCoordinate(TempArrayPos2);
                data[TempArrayPos2].InBiomeRegion = 1;

                if(CoordinateQueue.empty() == 0)
                {
                    if(DebugMessages)
                    {
                        fout << "\n Queue not empty.";
                        fout << "\n Left absolute value: " << aLeft;
                        fout << "\n Left InBiomeRegion: " << data[aLeft].InBiomeRegion;
                    }

                    if(aLeft > -1)
                    {
                        if(data[aLeft].Biome == CurrentBiome)
                        {
                            if(data[aLeft].InBiomeRegion == 0)
                            {
                                CoordinateQueue.push(aLeft);
                                NatureRegionsContainer[CurrentRegion].AddCoordinate(aLeft);
                                data[aLeft].region = CurrentRegion;
                                data[aLeft].InBiomeRegion = 1;
                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\n Right absolute value: " << aRight;
                        fout << "\n Right InBiomeRegion: " << data[aRight].InBiomeRegion;
                    }

                    if(aRight > 0)
                    {
                        if(data[aRight].Biome == CurrentBiome)
                        {
                            if(data[aRight].InBiomeRegion == 0)
                            {
                                CoordinateQueue.push(aRight);
                                NatureRegionsContainer[CurrentRegion].AddCoordinate(aRight);
                                data[aRight].region = CurrentRegion;
                                data[aRight].InBiomeRegion = 1;
                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\n Above absolute value: " << aAbove;
                        fout << "\n Above InBiomeRegion: " << data[aAbove].InBiomeRegion;
                    }

                    if(aAbove > -1)
                    {
                        if(data[aAbove].Biome == CurrentBiome)
                        {
                            if(data[aAbove].InBiomeRegion == 0)
                            {
                                CoordinateQueue.push(aAbove);
                                NatureRegionsContainer[CurrentRegion].AddCoordinate(aAbove);
                                data[aAbove].region = CurrentRegion;
                                data[aAbove].InBiomeRegion = 1;
                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\n Below absolute value: " << aBelow;
                        fout << "\n Below InBiomeRegion: " << data[aBelow].InBiomeRegion;
                    }

                    if(aBelow > 0)
                    {
                        if(data[aBelow].Biome == CurrentBiome)
                        {
                            if(data[aBelow].InBiomeRegion == 0)
                            {
                                CoordinateQueue.push(aBelow);
                                NatureRegionsContainer[CurrentRegion].AddCoordinate(aBelow);
                                data[aBelow].region = CurrentRegion;
                                data[aBelow].InBiomeRegion = 1;
                            }
                        }
                    }
                    CoordinateQueue.pop();
                }

                if(CoordinateQueue.empty() == 1)
                {
                    if(DebugMessages)
                    {
                        fout << "\n Queue empty.";
                    }

                    CurrentRegion++;
                    exit2 = 1;
                }
            }
        }


        if(GridY < YLimit && GridX <= XLimit)
        {
            GridY++;
        }

        else if(GridY == YLimit && GridX < XLimit)
        {
            GridY = 0;
            GridX++;
        }
        else if(GridY == YLimit && GridX == XLimit)
        {
            if(DebugMessages)
            {
                fout << "\n\n~~~END_OF_ENTRY~~~";
                fout.close();
            }

            exit = 1; //Exit condition.
        }

    }
    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";

    int RegionCount = (int)NatureRegionsContainer.size();
    std::cout << "\n\nNumber of Regions: " << RegionCount;
}

bool MapSystem::NatureRegion::Contains(int Position)
{
    for( std::vector <int>::iterator CurrentVectorPos = ContainedCoordinates.begin(); CurrentVectorPos != ContainedCoordinates.end(); CurrentVectorPos ++)
    {
        if( (*CurrentVectorPos) == Position)
        {
            return 1;
        }
    }
    return 0;
}

void MapSystem::NatureRegion::AddCoordinate(int Position)
{
    ContainedCoordinates.push_back(Position);
}

/*MapSystem::CartesianCoordinate MapSystem::GameMap::ConvertToCoordinate(int AbsolutePosition)
{
    MapSystem::CartesianCoordinate TempCoord;
    TempCoord.x = AbsolutePosition % x;
    TempCoord.y = AbsolutePosition / x;
    return TempCoord;
}*/

bool MapSystem::GameMap::RegionContainsCoordinate(int AbsolutePosition)
{
    for(std::vector <NatureRegion>::iterator CurrentVectorPos = NatureRegionsContainer.begin(); CurrentVectorPos!= NatureRegionsContainer.end(); CurrentVectorPos++ )
    {
        if((*CurrentVectorPos).Contains(AbsolutePosition))
        {
            return 1;
        }
    }
    return 0;
}

int MapSystem::GameMap::GetRiverDirection(int Position)
{
    if(data[Position].IsRiver == 1)
    {
        int Left = data[Position].Left();
        int Right = data[Position].Right();
        int Above = data[Position].Above();
        int Below = data[Position].Below();

        bool LeftIsRiver = 0;
        bool RightIsRiver = 0;
        bool AboveIsRiver = 0;
        bool BelowIsRiver = 0;

        if(Left > -1)
        {
            if(data[Left].z <= SeaLevel)
            {
                LeftIsRiver = 1;
            }
            if(data[Left].IsRiver == 1)
            {
                LeftIsRiver = 1;
            }
        }
        if(Left <= -1)
        {
            LeftIsRiver = 0;
        }

        if(Right > -1)
        {
            if(data[Right].z <= SeaLevel)
            {
                RightIsRiver = 1;
            }
            if(data[Right].IsRiver == 1)
            {
                RightIsRiver = 1;
            }
        }
        if(Right <= -1)
        {
            RightIsRiver = 0;
        }

        if(Above > -1)
        {
            if(data[Above].z <= SeaLevel)
            {
                AboveIsRiver = 1;
            }
            if(data[Above].IsRiver == 1)
            {
                AboveIsRiver = 1;
            }
        }
        if(Above <= -1)
        {
            AboveIsRiver = 0;
        }

        if(Below > -1)
        {
            if(data[Below].z <= SeaLevel)
            {
                BelowIsRiver = 1;
            }
            if(data[Below].IsRiver == 1)
            {
                BelowIsRiver = 1;
            }
        }
        if(Below <= -1)
        {
            BelowIsRiver = 0;
        }


        if(data[Position].IsRiverStartPoint == 0)
        {

        }
        if(LeftIsRiver == 0 && RightIsRiver == 0 && AboveIsRiver == 1 && BelowIsRiver == 1)
        {
            return 11;
        }

        if(LeftIsRiver == 0 && RightIsRiver == 1 && AboveIsRiver == 1 && BelowIsRiver == 0)
        {
            return 12;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 0 && AboveIsRiver == 1 && BelowIsRiver == 0)
        {
            return 13;
        }
        if(LeftIsRiver == 0 && RightIsRiver == 1 && AboveIsRiver == 0 && BelowIsRiver == 1)
        {
            return 14;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 0 && AboveIsRiver == 0 && BelowIsRiver == 1)
        {
            return 15;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 0 && AboveIsRiver == 1 && BelowIsRiver == 0)
        {
            return 16;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 1 && AboveIsRiver == 0 && BelowIsRiver == 0)
        {
            return 17;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 1 && AboveIsRiver == 1 && BelowIsRiver == 0)
        {
            return 18;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 1 && AboveIsRiver == 0 && BelowIsRiver == 1)
        {
            return 19;
        }
        if(LeftIsRiver == 0 && RightIsRiver == 1 && AboveIsRiver == 1 && BelowIsRiver == 1)
        {
            return 20;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 0 && AboveIsRiver == 1 && BelowIsRiver == 1)
        {
            return 21;
        }
        if(LeftIsRiver == 1 && RightIsRiver == 1 && AboveIsRiver == 1 && BelowIsRiver == 1)
        {
            return 22;
        }
        if(data[Position].IsRiverStartPoint == 1)
        {
            if(LeftIsRiver == 0 && RightIsRiver == 0 && AboveIsRiver == 0 && BelowIsRiver == 1)
            {
                return 11;
            }
            if(LeftIsRiver == 0 && RightIsRiver == 0 && AboveIsRiver == 1 && BelowIsRiver == 0)
            {
                return 11;
            }
            if(LeftIsRiver == 0 && RightIsRiver == 1 && AboveIsRiver == 0 && BelowIsRiver == 0)
            {
                return 17;
            }
            if(LeftIsRiver == 1 && RightIsRiver == 0 && AboveIsRiver == 0 && BelowIsRiver == 0)
            {
                return 17;
            }
        }
        return 11;
    }
    return 0;
}

void MapSystem::GameMap::SetRiverBaseColor(int Position)
{
    int leftr = data[data[Position].Left()].BaseColor.r;
    int leftg = data[data[Position].Left()].BaseColor.g;
    int leftb = data[data[Position].Left()].BaseColor.b;

    int rightr = data[data[Position].Right()].BaseColor.r;
    int rightg = data[data[Position].Right()].BaseColor.g;
    int rightb = data[data[Position].Right()].BaseColor.b;

    int abover = data[data[Position].Above()].BaseColor.r;
    int aboveg = data[data[Position].Above()].BaseColor.g;
    int aboveb = data[data[Position].Above()].BaseColor.b;

    int belowr = data[data[Position].Below()].BaseColor.r;
    int belowg = data[data[Position].Below()].BaseColor.g;
    int belowb = data[data[Position].Below()].BaseColor.b;

    int upperleftr = data[data[Position].UpperLeft()].BaseColor.r;
    int upperleftg = data[data[Position].UpperLeft()].BaseColor.g;
    int upperleftb = data[data[Position].UpperLeft()].BaseColor.b;

    int lowerleftr = data[data[Position].LowerLeft()].BaseColor.r;
    int lowerleftg = data[data[Position].LowerLeft()].BaseColor.g;
    int lowerleftb = data[data[Position].LowerLeft()].BaseColor.b;

    int upperrightr = data[data[Position].UpperRight()].BaseColor.r;
    int upperrightg = data[data[Position].UpperRight()].BaseColor.g;
    int upperrightb = data[data[Position].UpperRight()].BaseColor.b;

    int lowerrightr = data[data[Position].LowerRight()].BaseColor.r;
    int lowerrightg = data[data[Position].LowerRight()].BaseColor.g;
    int lowerrightb = data[data[Position].LowerRight()].BaseColor.b;

    int finalr = (leftr + rightr + abover + belowr + upperleftr + lowerleftr + upperrightr + lowerrightr) / 8;
    int finalg = (leftg + rightg + aboveg + belowg + upperleftg + lowerleftg + upperrightg + lowerrightg) / 8;
    int finalb = (leftb + rightb + aboveb + belowb + upperleftb + lowerleftb + upperrightb + lowerrightb) / 8;

    data[Position].BaseColor.r = (char)finalr;
    data[Position].BaseColor.g = (char)finalg;
    data[Position].BaseColor.b = (char)finalb;
}

void MapSystem::GameMap::SetMountainBaseColor(int Position)
{
    int SuccessCount = 0;

    int finalr = 0;
    int finalg = 0;
    int finalb = 0;

    bool DeepMountain = IsDeepMountain(Position);
    //std::cout << "\n Is Deep Mountain: " << DeepMountain;

    if(data[Position].Left() > -1)
    {
        if(DeepMountain)
        {
            int leftr = data[data[Position].Left()].BaseColor.r;
            int leftg = data[data[Position].Left()].BaseColor.g;
            int leftb = data[data[Position].Left()].BaseColor.b;

            finalr += leftr;
            finalg += leftg;
            finalb += leftb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].Left()].z < MountainLevel)
            {
                int leftr = data[data[Position].Left()].BaseColor.r;
                int leftg = data[data[Position].Left()].BaseColor.g;
                int leftb = data[data[Position].Left()].BaseColor.b;

                finalr += leftr;
                finalg += leftg;
                finalb += leftb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].Right() > -1)
    {
        if(DeepMountain)
        {
            int rightr = data[data[Position].Right()].BaseColor.r;
            int rightg = data[data[Position].Right()].BaseColor.g;
            int rightb = data[data[Position].Right()].BaseColor.b;

            finalr += rightr;
            finalg += rightg;
            finalb += rightb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].Right()].z < MountainLevel)
            {
                int rightr = data[data[Position].Right()].BaseColor.r;
                int rightg = data[data[Position].Right()].BaseColor.g;
                int rightb = data[data[Position].Right()].BaseColor.b;

                finalr += rightr;
                finalg += rightg;
                finalb += rightb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].Above() > -1)
    {
        if(DeepMountain)
        {
            int abover = data[data[Position].Above()].BaseColor.r;
            int aboveg = data[data[Position].Above()].BaseColor.g;
            int aboveb = data[data[Position].Above()].BaseColor.b;

            finalr += abover;
            finalg += aboveg;
            finalb += aboveb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].Above()].z < MountainLevel)
            {
                int abover = data[data[Position].Above()].BaseColor.r;
                int aboveg = data[data[Position].Above()].BaseColor.g;
                int aboveb = data[data[Position].Above()].BaseColor.b;

                finalr += abover;
                finalg += aboveg;
                finalb += aboveb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].Below() > -1)
    {
        if(DeepMountain)
        {
            int belowr = data[data[Position].Below()].BaseColor.r;
            int belowg = data[data[Position].Below()].BaseColor.g;
            int belowb = data[data[Position].Below()].BaseColor.b;

            finalr += belowr;
            finalg += belowb;
            finalb += belowg;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].Below()].z < MountainLevel)
            {
                int belowr = data[data[Position].Below()].BaseColor.r;
                int belowg = data[data[Position].Below()].BaseColor.g;
                int belowb = data[data[Position].Below()].BaseColor.b;

                finalr += belowr;
                finalg += belowb;
                finalb += belowg;

                SuccessCount++;
            }
        }
    }
    if(data[Position].UpperLeft() > -1)
    {
        if(DeepMountain)
        {
            int upperleftr = data[data[Position].UpperLeft()].BaseColor.r;
            int upperleftg = data[data[Position].UpperLeft()].BaseColor.g;
            int upperleftb = data[data[Position].UpperLeft()].BaseColor.b;

            finalr += upperleftr;
            finalg += upperleftg;
            finalb += upperleftb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].UpperLeft()].z < MountainLevel)
            {
                int upperleftr = data[data[Position].UpperLeft()].BaseColor.r;
                int upperleftg = data[data[Position].UpperLeft()].BaseColor.g;
                int upperleftb = data[data[Position].UpperLeft()].BaseColor.b;

                finalr += upperleftr;
                finalg += upperleftg;
                finalb += upperleftb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].LowerLeft() > -1)
    {
        if(DeepMountain)
        {
            int lowerleftr = data[data[Position].LowerLeft()].BaseColor.r;
            int lowerleftg = data[data[Position].LowerLeft()].BaseColor.g;
            int lowerleftb = data[data[Position].LowerLeft()].BaseColor.b;

            finalr += lowerleftr;
            finalg += lowerleftg;
            finalb += lowerleftb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].LowerLeft()].z < MountainLevel)
            {
                int lowerleftr = data[data[Position].LowerLeft()].BaseColor.r;
                int lowerleftg = data[data[Position].LowerLeft()].BaseColor.g;
                int lowerleftb = data[data[Position].LowerLeft()].BaseColor.b;

                finalr += lowerleftr;
                finalg += lowerleftg;
                finalb += lowerleftb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].UpperRight() > -1)
    {
        if(DeepMountain)
        {
            int upperrightr = data[data[Position].UpperRight()].BaseColor.r;
            int upperrightg = data[data[Position].UpperRight()].BaseColor.g;
            int upperrightb = data[data[Position].UpperRight()].BaseColor.b;

            finalr += upperrightr;
            finalg += upperrightg;
            finalb += upperrightb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].UpperRight()].z < MountainLevel)
            {
                int upperrightr = data[data[Position].UpperRight()].BaseColor.r;
                int upperrightg = data[data[Position].UpperRight()].BaseColor.g;
                int upperrightb = data[data[Position].UpperRight()].BaseColor.b;

                finalr += upperrightr;
                finalg += upperrightg;
                finalb += upperrightb;

                SuccessCount++;
            }
        }
    }
    if(data[Position].LowerRight() > -1)
    {
        if(DeepMountain)
        {
            int lowerrightr = data[data[Position].LowerRight()].BaseColor.r;
            int lowerrightg = data[data[Position].LowerRight()].BaseColor.g;
            int lowerrightb = data[data[Position].LowerRight()].BaseColor.b;

            finalr += lowerrightr;
            finalg += lowerrightg;
            finalb += lowerrightb;

            SuccessCount++;
        }
        else if(!DeepMountain)
        {
            if(data[data[Position].LowerRight()].z < MountainLevel)
            {
                int lowerrightr = data[data[Position].LowerRight()].BaseColor.r;
                int lowerrightg = data[data[Position].LowerRight()].BaseColor.g;
                int lowerrightb = data[data[Position].LowerRight()].BaseColor.b;

                finalr += lowerrightr;
                finalg += lowerrightg;
                finalb += lowerrightb;

                SuccessCount++;
            }
        }
    }

    std::cout << "\n\nSuccess Count: " << SuccessCount;
    std::cout << "\nFinal Red: " << finalr << " Final Green: " << finalg << " Final Blue: " << finalb;

    finalr /= SuccessCount;
    finalg /= SuccessCount;
    finalb /= SuccessCount;

    data[Position].BaseColor.r = (char)finalr;
    data[Position].BaseColor.g = (char)finalg;
    data[Position].BaseColor.b = (char)finalb;
}

int MapSystem::GameMap::GetDistance(int PositionOne, int PositionTwo)
{
    int x1 = PositionOne % x;
    int y1 = PositionTwo / x;

    int x2 = PositionTwo % x;
    int y2 = PositionTwo / x;

    int x3 = (int)pow(x2 - x1, 2);
    int y3 = (int)pow(y2 - y1, 2);

    return (int)sqrt(x3 + y3);
}

std::string MapSystem::GameMap::BiomeToString(int TileID)
{
    std::string BiomeString;

    if(data[TileID].Biome == 0)
    {
        BiomeString = "No Biome";
    }
    if(data[TileID].Biome == 1)
    {
        BiomeString = "Tundra";
    }
    if(data[TileID].Biome == 2)
    {
        BiomeString = "Snow";
    }
    if(data[TileID].Biome == 3)
    {
        BiomeString = "Desert";
    }
    if(data[TileID].Biome == 4)
    {
        BiomeString = "Grassland";
    }
    if(data[TileID].Biome == 5)
    {
        BiomeString = "Deciduous Forest";
    }
    if(data[TileID].Biome == 6)
    {
        BiomeString = "Marshland";
    }
    if(data[TileID].Biome == 7)
    {
        BiomeString = "Tropical Deciduous";
    }
    if(data[TileID].Biome == 8)
    {
        BiomeString = "Rainforest";
    }
    if(data[TileID].Biome == 9)
    {
        BiomeString = "Bare";
    }
    if(data[TileID].Biome == 10)
    {
        BiomeString = "Scorched";
    }
    if(data[TileID].Biome == 11)
    {
        BiomeString = "Water";
    }
    if(data[TileID].Biome == 12)
    {
        BiomeString = "Taiga";
    }
    if(data[TileID].Biome == 13)
    {
        BiomeString = "Ice";
    }
    if(data[TileID].Biome == 14)
    {
        BiomeString = "Savannah";
    }

    return BiomeString;
}
