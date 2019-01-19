#include "GameMap.h"

void MapSystem::WeatherSystemManager::Reset()
{
    while(!ContainedSystems.empty())
    {
        ContainedSystems.pop_back();
    }
    CurrentID = 0;
    IDCount = 0;
}

void MapSystem::WeatherSystemManager::IncrementModifiers()
{
    if(ModifierOne < ModOneMax)
    {
        ModifierOne += ModOneAdd;
    }
    else if(ModifierOne == ModOneMax)
    {
        ModifierOne = .01;
    }

    if(ModifierTwo < ModTwoMax)
    {
        ModifierTwo += ModTwoAdd;
    }
    else if(ModifierTwo == ModTwoMax)
    {
        ModifierTwo = .0001;
    }
}

int MapSystem::WeatherSystemManager::GetChannelHeight()
{
    srand(time(NULL));
    int ChannelWidth = 0;

    while(ChannelWidth < MinimumChannelHeight)
    {
        ChannelWidth = static_cast<int>(rand() * ModifierOne * ModifierTwo) % MaximumChannelHeight;
        IncrementModifiers();
    }
    return ChannelWidth;
}

void MapSystem::WeatherSystemManager::SetWindAngles()
{
    srand(time(NULL));
    int CurrentAngle;
    int CurrentRow = 0; //Current Y-Value.
    int ChannelHeight;

    while(CurrentRow <= CurrentMap->y - 1)//Check this less than, might need to change...
    {
        IncrementModifiers();
        ChannelHeight = GetChannelHeight();
        if(CurrentRow + ChannelHeight <= CurrentMap->y - 1)
        {
            CurrentAngle = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand() * rand()) % MaximumAngle;

            for(int i = CurrentMap->ConvertToAbsolute(1, CurrentRow); i <= CurrentMap->ConvertToAbsolute(CurrentMap->x - 1, CurrentRow + ChannelHeight); i++)
            {
                CurrentMap->data[i].WindAngle = CurrentAngle;
            }
            CurrentRow += ChannelHeight;
        }
        if(CurrentRow + ChannelHeight > CurrentMap->y - 1)
        {
            ChannelHeight = (CurrentMap->y - 1) - CurrentRow;
            CurrentAngle = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand() * rand()) % MaximumAngle;

            for(int i = CurrentMap->ConvertToAbsolute(1, CurrentRow); i <= CurrentMap->ConvertToAbsolute(CurrentMap->x - 1, CurrentRow + ChannelHeight); i++)
            {
                CurrentMap->data[i].WindAngle = CurrentAngle;
            }
            CurrentRow = CurrentMap->y;
        }

    }
}

void MapSystem::WeatherSystemManager::ApplyNoiseToWindAngles()
{
    for(int i = 0; i < (CurrentMap->x * CurrentMap->y) - 1; i++)
    {
        int Noise = static_cast<int>(rand() * scaled_octave_noise_3d(15, .99, .005, 1, 0, MaximumNoiseAngle, CurrentMap->data[i].y, CurrentMap->data[i].z, CurrentMap->data[i].x)) % MaximumNoiseAngle;

        CurrentMap->data[i].WindAngle += Noise;
    }
}

int MapSystem::WeatherSystemManager::AddSystem()
{
    ContainedSystems.push_back(MapSystem::WeatherSystem());
    CurrentID++;
    IDCount++;

    return (CurrentID - 1);
}

int MapSystem::WeatherSystemManager::GetStartTile()
{
    srand(time(NULL));
    int StartPosition = -1;
    while(StartPosition < 0 && UsedStartPosition(StartPosition))
    {
        StartPosition = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % ((CurrentMap->x * CurrentMap->y) - 1);
        IncrementModifiers();
    }
    return StartPosition;
}

int MapSystem::WeatherSystemManager::GetStartRadius()
{
    if(UseVaryingRadius)
    {
        int Radius = -1;
        while(Radius < MinimumRadius || Radius > MaximumRadius)
        {
            Radius = static_cast<int>(rand() * ModifierOne * ModifierTwo) % MaximumRadius;
            IncrementModifiers();
        }
        return Radius;
    }
    else if(!UseVaryingRadius)
    {
        return ConstantRadius;
    }
}

int MapSystem::WeatherSystemManager::GetStartMoveSpeed()
{
    if(UseVaryingStartSpeed)
    {
        int StartSpeed = -1;
        while(StartSpeed < MinimumStartSpeed || StartSpeed > MaximumStartSpeed)
        {
            StartSpeed = static_cast<int>(rand() * ModifierOne * ModifierTwo) % MaximumStartSpeed;
            IncrementModifiers();
        }
        return StartSpeed;
    }
    else if(!UseVaryingStartSpeed)
    {
        return ConstantStartSpeed;
    }
}

bool MapSystem::WeatherSystemManager::UsedStartPosition(int Position)
{
    if(Position < 0)
    {
        return 1;
    }
    for(std::vector <int>::iterator VectorPosition = StartPositions.begin(); VectorPosition != StartPositions.end(); VectorPosition++)
    {
        if((*VectorPosition) == Position)
        {
            return 1;
        }
    }
    return 0;
}

int MapSystem::WeatherSystemManager::GetStartMoisture()
{
    if(UseVaryingStartMoisture)
    {
        int StartMoisture = -1;
        while(StartMoisture < MinimumStartMoisture || StartMoisture > MaximumStartMoisture)
        {
            StartMoisture = static_cast<int>(rand() * ModifierOne * ModifierTwo) % MaximumStartMoisture;
            IncrementModifiers();
        }
        return StartMoisture;
    }
    else if(!UseVaryingStartMoisture)
    {
        return ConstantStartMoisture;
    }
}

float MapSystem::WeatherSystemManager::PropagateRainfall(int SystemID)
{
    int YDifference;
    int XDifference;
    int Radius = ContainedSystems[SystemID].Radius;
    int Center = ContainedSystems[SystemID].CenterTile;
    int CenterX = Center % CurrentMap->x;
    int CenterY = Center / CurrentMap->x;
    int CurrentX = CenterX;
    int CurrentY;

    if(CenterY - Radius < 0)
    {
        CurrentY = 0;
    }
    else if(CenterY - Radius >= 0)
    {
        CurrentY = CenterY - Radius;
    }

    while(CurrentY <= CenterY)
    {
        YDifference = abs(CurrentY - CenterY) * 2;
        //CurrentX = sqrt((pow(Radius, 2) - pow(CurrentY, 2)));
        CurrentX = CenterX - sqrt(abs((-1 * pow(CurrentY - CenterY, 2)) + pow(Radius, 2)));
        //CurrentX = CenterX - sqrt((-1 * pow(CurrentY - CenterY, 2)) + pow(Radius, 2));
        if(CurrentX < 0)
        {
            CurrentX = 0;
        }
        //std::cout << "\n\nCurrent X: " << CurrentX << "\nCurrentY: " << CurrentY << "\nCenter X: " << CenterX << "\nCenter Y: " << CenterY << "\nRadius: " << Radius;
        while(CurrentX <= CenterX)
        {
            XDifference = abs(CurrentX - CenterX) * 2;

            int NewX;
            int NewY;

            if(CurrentX + XDifference <= CurrentMap->x - 1)
            {
                NewX = CurrentX + XDifference;
            }
            else if(CurrentX + XDifference > CurrentMap->x - 1)
            {
                NewX = CurrentMap->x - 1;
            }

            if(CurrentY + YDifference <= CurrentMap->y - 1)
            {
                NewY = CurrentY + YDifference;
            }
            else if(CurrentY + YDifference > CurrentMap->y - 1)
            {
                NewY = CurrentMap->y - 1;
            }

            if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].z > CurrentMap->SeaLevel)
            {
                if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) <= 255)
                {
                    (CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].rainfall) += (ContainedSystems[SystemID].Moisture / RainfallDivisor);
                }
                else if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) > 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].rainfall = 255;
                }
            }
            if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, CurrentY)].z > CurrentMap->SeaLevel)
            {
                if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, CurrentY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) <= 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, CurrentY)].rainfall += (ContainedSystems[SystemID].Moisture / RainfallDivisor);
                }
                else if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, CurrentY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) > 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, CurrentY)].rainfall = 255;
                }
            }
            if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, NewY)].z > CurrentMap->SeaLevel)
            {
                if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, NewY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) <= 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, NewY)].rainfall += (ContainedSystems[SystemID].Moisture / RainfallDivisor);
                }
                else if(CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, NewY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) > 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, NewY)].rainfall = 255;
                }
            }
            if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, NewY)].z > CurrentMap->SeaLevel)
            {
                if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, NewY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) <= 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, NewY)].rainfall += (ContainedSystems[SystemID].Moisture / RainfallDivisor);
                }
                else if(CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, NewY)].rainfall + (ContainedSystems[SystemID].Moisture / RainfallDivisor) > 255)
                {
                    CurrentMap->data[CurrentMap->ConvertToAbsolute(NewX, NewY)].rainfall = 255;
                }
            }

            //std::cout << "\n\nCurrent Tile: " << CurrentMap->ConvertToAbsolute(CurrentX, CurrentY) << "\nTile Rainfall: " << CurrentMap->data[CurrentMap->ConvertToAbsolute(CurrentX, CurrentY)].rainfall;

            CurrentX++;
        }
        CurrentY++;
    }

    if(CurrentMap->data[ContainedSystems[SystemID].CenterTile].z > CurrentMap->SeaLevel && CurrentMap->data[ContainedSystems[SystemID].CenterTile].z < CurrentMap->MountainLevel)
    {
        if(ContainedSystems[SystemID].Moisture - (255 / RainfallDivisor) >= 0)
        {
            ContainedSystems[SystemID].Moisture -= 255 / RainfallDivisor;
        }
        if(ContainedSystems[SystemID].Moisture - (255 / RainfallDivisor) < 0)
        {
            ContainedSystems[SystemID].Moisture = 0;
        }
    }
    /*if(CurrentMap->data[ContainedSystems[SystemID].CenterTile].z <= CurrentMap->SeaLevel)
    {
        if(ContainedSystems[SystemID].Moisture + (255 / CloudgainDivisor) <= 255)
        {
            ContainedSystems[SystemID].Moisture += 255 / CloudgainDivisor;
        }
        if(ContainedSystems[SystemID].Moisture + (255 / CloudgainDivisor) > 255)
        {
            ContainedSystems[SystemID].Moisture = 255;
        }
    }
    if(CurrentMap->data[ContainedSystems[SystemID].CenterTile].z >= CurrentMap->MountainLevel)
    {
        if(ContainedSystems[SystemID].Moisture - ((255 / RainfallDivisor) * 2) >= 0)
        {
            ContainedSystems[SystemID].Moisture -= (255 / RainfallDivisor) * 2;
        }
        if(ContainedSystems[SystemID].Moisture - ((255 / RainfallDivisor) * 2) < 0)
        {
            ContainedSystems[SystemID].Moisture = 0;
        }
    }*/

    return 0;

}

int MapSystem::WeatherSystemManager::GetResultantAngle(int AngleOne, int AngleTwo)
{
    return abs(AngleOne - AngleTwo) / 2;//Must change when varying wind speeds are added.
}

void MapSystem::WeatherSystemManager::RunWeather()
{
    for(int System = 0; System <= TotalSystems; System++)
    {
        int CurrentSystem = AddSystem();

        ContainedSystems[CurrentSystem].CenterTile = GetStartTile();
        int CurrentCenter = ContainedSystems[CurrentSystem].CenterTile;
        //std::cout << "\n\nCurrent System ID: " << i <<"\nCurrent Center Tile: " << CurrentCenter;

        ContainedSystems[CurrentSystem].MovementAngle = CurrentMap->data[CurrentCenter].WindAngle;
        ContainedSystems[CurrentSystem].Radius = GetStartRadius();
        ContainedSystems[CurrentSystem].MovementSpeed = GetStartMoveSpeed();
        ContainedSystems[CurrentSystem].Moisture = GetStartMoisture();
        //std::cout << "\n\nCurrent System: " << CurrentSystem << "\nStart Moisture: " << ContainedSystems[CurrentSystem].Moisture;

        for(int Step = 0; Step < StepLimit; Step++)
        {
            float PercentDrop = PropagateRainfall(CurrentSystem);
            ContainedSystems[CurrentSystem].MovementAngle = GetResultantAngle(ContainedSystems[CurrentSystem].MovementAngle, CurrentMap->data[CurrentCenter].WindAngle);

            int CurrentX = ContainedSystems[CurrentSystem].CenterTile % CurrentMap->x;
            int CurrentY = ContainedSystems[CurrentSystem].CenterTile / CurrentMap->x;
            int XDelta = ContainedSystems[CurrentSystem].MovementSpeed * cos(ContainedSystems[CurrentSystem].MovementAngle);
            int YDelta = ContainedSystems[CurrentSystem].MovementSpeed * sin(ContainedSystems[CurrentSystem].MovementAngle);
            int NewX;
            int NewY;


            if(CurrentX + XDelta > CurrentMap->x - 1)
            {
                NewX = CurrentMap->x - 1;
            }
            else if(CurrentX + XDelta < 0)
            {
                NewX = 0;
            }
            else if(CurrentX + XDelta >= 0 && CurrentX + XDelta <= CurrentMap->x - 1)
            {
                NewX = CurrentX + XDelta;
            }

            if(CurrentY + YDelta > CurrentMap->y - 1)
            {
                NewY = CurrentMap->y - 1;
            }
            else if(CurrentY + YDelta < 0)
            {
                NewY = 0;
            }
            else if(CurrentY + YDelta >= 0 && CurrentY + YDelta <= CurrentMap->y - 1)
            {
                NewY = CurrentY + YDelta;
            }

            ContainedSystems[CurrentSystem].CenterTile = CurrentMap->ConvertToAbsolute(NewX, NewY);
        }
    }
}
