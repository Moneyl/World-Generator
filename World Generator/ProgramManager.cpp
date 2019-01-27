#include "ProgramManager.h"

sf::Color ProgramManager::GetRandomColor()
{
	int r = -1;
	int g = -1;
	int b = -1;

	if(UseColorRestraints)
	{
		while(r < ColorMinimum || r > ColorMaximum)
		{
			r = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % ColorMaximum;
		}
		while(g < ColorMinimum || g > ColorMaximum)
		{
			g = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % ColorMaximum;
		}
		while(b < ColorMinimum || b > ColorMaximum)
		{
			b = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % ColorMaximum;
		}
	}
	else if(!UseColorRestraints)
	{
		while(r < ColorMinimum || r > ColorMaximum)
		{
			r = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % 255;
		}
		while(g < ColorMinimum || g > ColorMaximum)
		{
			g = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % 255;
		}
		while(b < ColorMinimum || b > ColorMaximum)
		{
			b = static_cast<int>(rand() * ModifierOne * ModifierTwo * rand()) % 255;
		}
	}


	sf::Color TempColor;
	TempColor.r = r;
	TempColor.g = g;
	TempColor.b = b;

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

	return TempColor;
}

void ProgramManager::DrawHeightMap(bool ColorWater)
{
	sf::Color TempColor;

	int GridX;
	int GridY;

	for(int i = 0; i < (CurrentMap->x * CurrentMap->y) - 1; i++)
	{
		GridX = i % CurrentMap->x;
		GridY = i / CurrentMap->x;

		if(ColorWater ==  1)
		{
			if(CurrentMap->data[i].z <= CurrentMap->SeaLevel)
			{
				TempColor.r = WaterColor.r;
				TempColor.g = WaterColor.g;
				TempColor.b = WaterColor.b + CurrentMap->data[i].z;
				TempColor.a = WaterColor.a;
			}
			if(CurrentMap->data[i].IsRiver == 1)
			{
				TempColor.r = 81;
				TempColor.g = 113;//128 Check if it makes a better color.
				TempColor.b = 167;
			}
			if(DisplayRiverStartPoints)
			{
				if(CurrentMap->data[i].IsRiverStartPoint == 1)
				{
					TempColor.r = 255;
					TempColor.g = 0;
					TempColor.b = 0;
				}
			}
			if(CurrentMap->data[i].z > CurrentMap->SeaLevel && CurrentMap->data[i].IsRiver == 0)
			{
				TempColor.r = CurrentMap->data[i].z;
				TempColor.g = CurrentMap->data[i].z;
				TempColor.b = CurrentMap->data[i].z;
			}
		}
		else if(ColorWater == 0)
		{
			TempColor.r = CurrentMap->data[i].z;
			TempColor.g = CurrentMap->data[i].z;
			TempColor.b = CurrentMap->data[i].z;
		}
		MapImage.setPixel(GridX, GridY, TempColor);
	}

	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/HeightMapExport.png");
	}
}

void ProgramManager::DrawTemperatureMap(bool Greyscale)
{
	sf::Color TempColor;

	int GridX;
	int GridY;

	for(int i = 0; i < (CurrentMap->x * CurrentMap->y) - 1; i++)
	{
		GridX = i % CurrentMap->x;
		GridY = i / CurrentMap->x;

		if(!Greyscale)
		{
			TempColor.r = CurrentMap->data[i].temperature;
			TempColor.g = 0;
			TempColor.b = 255 - CurrentMap->data[i].temperature;
		}
		if(Greyscale)
		{
			TempColor.r = CurrentMap->data[i].temperature;
			TempColor.g = CurrentMap->data[i].temperature;
			TempColor.b = CurrentMap->data[i].temperature;
		}

		MapImage.setPixel(GridX, GridY, TempColor);
	}
	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/TemperatureMapExport.png");
	}
}

void ProgramManager::DrawRainfallMap(bool Greyscale, bool ColorWater)
{
	sf::Color TempColor;

	int GridX;
	int GridY;

	for(int i = 0; i < (CurrentMap->x * CurrentMap->y) - 1; i++)
	{
		GridX = i % CurrentMap->x;
		GridY = i / CurrentMap->x;

		if(Greyscale)
		{
			if(ColorWater)
			{
				if(CurrentMap->data[i].z <= CurrentMap->SeaLevel)
				{
					TempColor.r = WaterColor.r;
					TempColor.g = WaterColor.g;
					TempColor.b = WaterColor.b + CurrentMap->data[i].z;
				}
				else
				{
					TempColor.r = CurrentMap->data[i].rainfall;
					TempColor.g = CurrentMap->data[i].rainfall;
					TempColor.b = CurrentMap->data[i].rainfall;
				}
			}
			else if(!ColorWater)
			{
				TempColor.r = CurrentMap->data[i].rainfall;
				TempColor.g = CurrentMap->data[i].rainfall;
				TempColor.b = CurrentMap->data[i].rainfall;
			}
		}

		MapImage.setPixel(GridX, GridY, TempColor);
	}
	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/RainfallMapExport.png");
	}
}

void ProgramManager::DrawBiomeMap()
{
	int MapSizeX = CurrentMap->x;
	int MapSizeY = CurrentMap->y;

	sf::Color TempColor;
	TempColor.r = 255;
	TempColor.g = 255;
	TempColor.b = 255;
	TempColor.a = 255;

	sf::Color TundraColor;
	TundraColor.r = 89;
	TundraColor.g = 141;
	TundraColor.b = 232;
	TundraColor.a = 255;

	sf::Color SnowColor;
	SnowColor.r = 151;//206//233//193
	SnowColor.g = 235;//199//226
	SnowColor.b = 255;//194//221
	SnowColor.a = 255;

	sf::Color MountainSnowColor;
	MountainSnowColor.r = 233;//206//233//193
	MountainSnowColor.g = 226;//199//226
	MountainSnowColor.b = 221;//194//221
	MountainSnowColor.a = 255;

	sf::Color DesertColor;
	DesertColor.r = 188;
	DesertColor.g = 146;
	DesertColor.b = 103;
	DesertColor.a = 255;

	sf::Color GrasslandColor;
	GrasslandColor.r = 157;//129 129 90
	GrasslandColor.g = 133; //91 92 58
	GrasslandColor.b = 75;
	GrasslandColor.a = 255;

	sf::Color ForestColor;
	ForestColor.r = 50;
	ForestColor.g = 60;
	ForestColor.b = 20;
	ForestColor.a = 255;

	sf::Color MarshColor;
	MarshColor.r = 94;
	MarshColor.g = 101;
	MarshColor.b = 78;
	MarshColor.a = 255;

	sf::Color TForestColor;
	TForestColor.r = 43;
	TForestColor.g = 46;
	TForestColor.b = 43;
	TForestColor.a = 255;

	sf::Color RainforestColor;
	RainforestColor.r = 43;
	RainforestColor.g = 46;
	RainforestColor.b = 43;
	RainforestColor.a = 255;

	sf::Color BareColor;
	BareColor.r = 171;//76
	BareColor.g = 166;//71
	BareColor.b = 163;//68
	BareColor.a = 255;

	sf::Color ScorchedColor;
	ScorchedColor.r = 83;
	ScorchedColor.g = 83;
	ScorchedColor.b = 83;
	ScorchedColor.a = 255;

	sf::Color TaigaColor;
	TaigaColor.r = 80;
	TaigaColor.g = 96;
	TaigaColor.b = 60;
	TaigaColor.a = 255;

	sf::Color IceColor;
	IceColor.r = 30;
	IceColor.g = 151;
	IceColor.b = 162;
	IceColor.a = 255;

	sf::Color SavannahColor;
	SavannahColor.r = 165;
	SavannahColor.g = 121;
	SavannahColor.b = 56;
	SavannahColor.a = 255;

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

	int GridX = 0;
	int GridY = 0;

	int XLimit = CurrentMap->x - 1;
	int YLimit = CurrentMap->y - 1;

	while(GridX <= XLimit && GridY <= YLimit)
	{
		int TempArrayPos = CurrentMap->ConvertToAbsolute(GridX, GridY);

		if(CurrentMap->data[TempArrayPos].Biome == 0)
		{
			if(CurrentMap->data[TempArrayPos].z <= CurrentMap->SeaLevel)
			{
				TempColor.r = WaterColor.r;
				TempColor.g = WaterColor.g;
				TempColor.b = WaterColor.b + CurrentMap->data[TempArrayPos].z;
				TempColor.a = WaterColor.a;

				CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
				CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
				CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			}
			if(CurrentMap->data[TempArrayPos].IsRiver == 1)
			{
				TempColor.r = 81;
				TempColor.g = 113;//128 Check if it makes a better color.
				TempColor.b = 167;
				TempColor.a = 255;

				CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
				CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
				CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;
			}
			if(DisplayRiverStartPoints)
			{
				if(CurrentMap->data[TempArrayPos].IsRiverStartPoint == 1)
				{
					TempColor.r = 255;
					TempColor.g = 0;
					TempColor.b = 0;
					TempColor.a = 255;

					CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
					CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
					CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;
				}
			}
			if(CurrentMap->data[TempArrayPos].z > CurrentMap->SeaLevel && CurrentMap->data[TempArrayPos].IsRiver == 0)
			{
				TempColor.r = CurrentMap->data[TempArrayPos].z;
				TempColor.g = CurrentMap->data[TempArrayPos].z;
				TempColor.b = CurrentMap->data[TempArrayPos].z;
				TempColor.a = 255;

				CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
				CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
				CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;
			}
			MapImage.setPixel(GridX, GridY, TempColor);
		}
		if(CurrentMap->data[TempArrayPos].Biome == 1)
		{
			TempColor.r = TundraColor.r;
			TempColor.g = TundraColor.g + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);
			TempColor.b = TundraColor.b;
			TempColor.a = TundraColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 2)
		{
			//TempColor.r = SnowColor.r - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
			//TempColor.g = SnowColor.g - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
			//TempColor.b = SnowColor.b - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
			//TempColor.a = SnowColor.a;

			int GreenChange = (255 - SnowColor.g) / (CurrentMap->MountainLevel - CurrentMap->SeaLevel);

			if(CurrentMap->data[TempArrayPos].z < CurrentMap->MountainLevel)
			{
				TempColor.r = SnowColor.r + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel - 1);
				TempColor.g = SnowColor.g + ((CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel - 1) * GreenChange);
				TempColor.b = SnowColor.b;// + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel - 1);
				TempColor.a = SnowColor.a;
			}
			if(CurrentMap->data[TempArrayPos].z >= CurrentMap->MountainLevel)
			{
				TempColor.r = MountainSnowColor.r - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
				TempColor.g = MountainSnowColor.g - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
				TempColor.b = MountainSnowColor.b - (CurrentMap->data[TempArrayPos].z - CurrentMap->SnowLevel - 1);
				TempColor.a = MountainSnowColor.a;
			}

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 3)
		{
			TempColor.r = DesertColor.r + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);
			TempColor.g = DesertColor.g + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);
			TempColor.b = DesertColor.b + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);
			TempColor.a = DesertColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 4)
		{
			TempColor.r = GrasslandColor.r + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel) / 3;
			TempColor.g = GrasslandColor.g + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel) / 1.25;
			TempColor.b = GrasslandColor.b;
			TempColor.a = GrasslandColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 5)
		{
			TempColor.r = ForestColor.r;
			TempColor.g = ForestColor.g + CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel;
			TempColor.b = ForestColor.b;
			TempColor.a = ForestColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 6)
		{
			TempColor.r = MarshColor.r - (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel) * .5;
			TempColor.g = MarshColor.g;
			TempColor.b = MarshColor.b - (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel) * .5;
			TempColor.a = MarshColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 7)
		{
			TempColor.r = TForestColor.r;
			TempColor.g = TForestColor.g + CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel;
			TempColor.b = TForestColor.b;
			TempColor.a = TForestColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 8)
		{
			TempColor.r = RainforestColor.r;
			TempColor.g = RainforestColor.g + CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel;
			TempColor.b = RainforestColor.b;
			TempColor.a = RainforestColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 9)
		{
			TempColor.r = BareColor.r - CurrentMap->data[TempArrayPos].z - CurrentMap->MountainLevel - 1;
			TempColor.g = BareColor.g - CurrentMap->data[TempArrayPos].z - CurrentMap->MountainLevel - 1;
			TempColor.b = BareColor.b - CurrentMap->data[TempArrayPos].z - CurrentMap->MountainLevel - 1;
			TempColor.a = BareColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 10)
		{
			TempColor.r = ScorchedColor.r + CurrentMap->data[TempArrayPos].z - 199;
			TempColor.g = ScorchedColor.g + CurrentMap->data[TempArrayPos].z - 199;
			TempColor.b = ScorchedColor.b + CurrentMap->data[TempArrayPos].z - 199;
			TempColor.a = ScorchedColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 11)
		{

			TempColor.r = WaterColor.r;
			TempColor.g = WaterColor.g;
			TempColor.b = WaterColor.b + CurrentMap->data[TempArrayPos].z;
			TempColor.a = WaterColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 12)
		{
			TempColor.r = WaterColor.r;
			TempColor.g = WaterColor.g;
			TempColor.b = WaterColor.b + CurrentMap->data[TempArrayPos].z;
			TempColor.a = WaterColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 13)
		{
			TempColor.r = IceColor.r;
			TempColor.g = IceColor.g;
			TempColor.b = IceColor.b + CurrentMap->data[TempArrayPos].z;
			TempColor.a = IceColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		else if(CurrentMap->data[TempArrayPos].Biome == 14)
		{
			TempColor.r = SavannahColor.r + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);// / 3;
			TempColor.g = SavannahColor.g + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);// / 1.25;
			TempColor.b = SavannahColor.b + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel);
			TempColor.a = SavannahColor.a;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}

		if(CurrentMap->data[TempArrayPos].IsRiver == 1)
		{
			TempColor.r = 81;
			TempColor.g = 113;
			TempColor.b = 167;
			TempColor.a = 255;

			CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
			CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
			CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

			MapImage.setPixel(GridX, GridY, TempColor);
		}
		if(DisplayRiverStartPoints)
		{
			if(CurrentMap->data[TempArrayPos].IsRiverStartPoint == 1)
			{
				TempColor.r = 255;
				TempColor.g = 0;
				TempColor.b = 0;
				TempColor.a = 255;

				CurrentMap->data[TempArrayPos].BaseColor.r = TempColor.r;
				CurrentMap->data[TempArrayPos].BaseColor.g = TempColor.g;
				CurrentMap->data[TempArrayPos].BaseColor.b = TempColor.b;

				MapImage.setPixel(GridX, GridY, TempColor);
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
			GridX = XLimit + 1; //Exit condition.
		}
	}
	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/BiomeMapExport.png");
	}
}

void ProgramManager::DrawRegionMap()
{
	int ArraySize = (CurrentMap->x * CurrentMap->y) - 1;
	sf::Color TempColor;

	int Counter = 0;
	for(int i = 0; i < CurrentMap->NatureRegionsContainer.size(); i++)
	{
		if(!CurrentMap->NatureRegionsContainer[i].ColorSet)
		{
			TempColor = GetRandomColor();

			CurrentMap->NatureRegionsContainer[i].RegionColor.r = TempColor.r;
			CurrentMap->NatureRegionsContainer[i].RegionColor.g = TempColor.g;
			CurrentMap->NatureRegionsContainer[i].RegionColor.b = TempColor.b;
			CurrentMap->NatureRegionsContainer[i].ColorSet = 1;
		}
		else if(CurrentMap->NatureRegionsContainer[i].ColorSet)
		{
			TempColor.r = CurrentMap->NatureRegionsContainer[i].RegionColor.r;
			TempColor.g = CurrentMap->NatureRegionsContainer[i].RegionColor.g;
			TempColor.b = CurrentMap->NatureRegionsContainer[i].RegionColor.b;
		}
		for(int i2= 0; i2 < CurrentMap->NatureRegionsContainer[i].ContainedCoordinates.size(); i2++)
		{
			int CurrentPos = CurrentMap->NatureRegionsContainer[i].ContainedCoordinates[i2];
			int XPos = CurrentPos % CurrentMap->x;
			int YPos = CurrentPos / CurrentMap->x;
			MapImage.setPixel(XPos, YPos, TempColor);
		}
	}

	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/RegionMapExport.png");
	}
}

void ProgramManager::DrawHeightRegionMap()
{
	sf::Color TempColor;

	for(int i = 0; i < CurrentHRM->HeightTierContainer.size(); i++)
	{
		if(!CurrentHRM->HeightTierContainer[i].ColorSet)
		{
			TempColor = GetRandomColor();
			CurrentHRM->HeightTierContainer[i].RegionColor.r = TempColor.r;
			CurrentHRM->HeightTierContainer[i].RegionColor.g = TempColor.g;
			CurrentHRM->HeightTierContainer[i].RegionColor.b = TempColor.b;

			CurrentHRM->HeightTierContainer[i].ColorSet = 1;
		}
	}

	for(int i = 0; i < ((CurrentMap->x * CurrentMap->y) - 1); i++)
	{
		MapImage.setPixel(CurrentMap->data[i].x, CurrentMap->data[i].y, CurrentHRM->HeightTierContainer[CurrentMap->data[i].HeightTier].RegionColor);
	}
	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/HeightRegionMapExport.png");
	}
}

void ProgramManager::DrawWaterRegionMap()
{
	int ArraySize = (CurrentMap->x * CurrentMap->y) - 1;
	sf::Color TempColor;
	TempColor.a = 255;

	int Counter = 0;
	for(int i = 0; i < CurrentWRM->ContainedRegions.size(); i++)
	{
		if(!CurrentWRM->ContainedRegions[i].ColorSet)
		{
			TempColor = GetRandomColor();

			CurrentWRM->ContainedRegions[i].RegionColor.r = TempColor.r;
			CurrentWRM->ContainedRegions[i].RegionColor.g = TempColor.g;
			CurrentWRM->ContainedRegions[i].RegionColor.b = TempColor.b;
			CurrentWRM->ContainedRegions[i].ColorSet = 1;
		}
		else if(CurrentWRM->ContainedRegions[i].ColorSet)
		{
			TempColor.r = CurrentWRM->ContainedRegions[i].RegionColor.r;
			TempColor.g = CurrentWRM->ContainedRegions[i].RegionColor.g;
			TempColor.b = CurrentWRM->ContainedRegions[i].RegionColor.b;
		}
		for(int i2 = 0; i2 < CurrentWRM->ContainedRegions[i].ContainedCoordinates.size(); i2++)
		{
			int CurrentPos = CurrentWRM->ContainedRegions[i].ContainedCoordinates[i2];

			int XPos = CurrentMap->data[CurrentPos].x;
			int YPos = CurrentMap->data[CurrentPos].y;
			MapImage.setPixel(XPos, YPos, TempColor);
		}
	}

	for(int i = 0; i < CurrentMap->x * CurrentMap->y; i++)
	{
		if(CurrentMap->data[i].InWaterRegion == 0)
		{
			int XPos = CurrentMap->data[i].x;
			int YPos = CurrentMap->data[i].y;

			TempColor.r = CurrentMap->data[i].z;
			TempColor.g = CurrentMap->data[i].z;
			TempColor.b = CurrentMap->data[i].z;

			MapImage.setPixel(XPos, YPos, TempColor);
		}
	}

	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/WaterRegionMapExport.png");
	}
}

sf::Color ProgramManager::GetTileColor(int Position, sf::Image *MapImage)
{
	return MapImage->getPixel(Position % CurrentMap->x, Position / CurrentMap->x);
}

void ProgramManager::BlendBiomeColors()
{
	sf::Image MapImage;
	MapImage = MapTexture.copyToImage();

	sf::Color TempColor;
	int TempRed;
	int TempGreen;
	int TempBlue;
	int SuccessCount;

	for(int i = 0; i < CurrentMap->MapSize - 1; i++)
	{
		if(CurrentMap->data[i].z > CurrentMap->SeaLevel)
		{
			if(CurrentMap->data[i].z < CurrentMap->MountainLevel)
			{
				if(CurrentMap->IsBiomeBorder(i))
				{
					TempRed = GetTileColor(i, &MapImage).r;
					TempGreen = GetTileColor(i, &MapImage).g;
					TempBlue = GetTileColor(i, &MapImage).b;
					SuccessCount = 1;

					if(CurrentMap->data[i].Left() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Left()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Left()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].Left(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].Left(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].Left(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Right() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Right()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Right()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].Right(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].Right(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].Right(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Above() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Above()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Above()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].Above(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].Above(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].Above(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Below() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Below()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Below()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].Below(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].Below(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].Below(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].UpperLeft() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].UpperLeft()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].UpperLeft()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].UpperLeft(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].UpperLeft(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].UpperLeft(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].LowerLeft() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].LowerLeft()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].LowerLeft()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].LowerLeft(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].LowerLeft(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].LowerLeft(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].UpperRight() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].UpperRight()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].UpperRight()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].UpperRight(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].UpperRight(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].UpperRight(), &MapImage).b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].LowerRight() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].LowerRight()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].LowerRight()].z < CurrentMap->MountainLevel)
							{
								TempRed += GetTileColor(CurrentMap->data[i].LowerRight(), &MapImage).r;
								TempGreen += GetTileColor(CurrentMap->data[i].LowerRight(), &MapImage).g;
								TempBlue += GetTileColor(CurrentMap->data[i].LowerRight(), &MapImage).b;

								SuccessCount++;
							}
						}
					}

					if(SuccessCount > 0)
					{
						TempRed /= SuccessCount;
						TempGreen /= SuccessCount;
						TempBlue /= SuccessCount;

						TempColor.r = TempRed;
						TempColor.g = TempGreen;
						TempColor.b = TempBlue;

						MapImage.setPixel(i % CurrentMap->x, i / CurrentMap->x, TempColor);
					}
				}
			}
		}
	}

	MapTexture.loadFromImage(MapImage);
	if(ExportMapImages)
	{
		MapImage.saveToFile("MapExports/BlendedBiomeMapExport.png");
	}
}

void ProgramManager::BlendTileBackgrounds()
{
	int TempRed;
	int TempGreen;
	int TempBlue;

	for(int i = 0; i < CurrentMap->MapSize - 1; i++)
	{
		if(CurrentMap->data[i].z > CurrentMap->SeaLevel)
		{
			if(CurrentMap->data[i].z < CurrentMap->MountainLevel)
			{
				if(CurrentMap->IsBiomeBorder(i))
				{
					TempRed = CurrentMap->data[i].BaseColor.r;
					TempGreen = CurrentMap->data[i].BaseColor.g;
					TempBlue = CurrentMap->data[i].BaseColor.b;

					int SuccessCount = 1;

					if(CurrentMap->data[i].Left() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Left()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Left()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].Left()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].Left()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].Left()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Right() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Right()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Right()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].Right()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].Right()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].Right()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Above() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Above()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Above()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].Above()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].Above()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].Above()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].Below() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].Below()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].Below()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].Below()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].Below()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].Below()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].UpperLeft() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].UpperLeft()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].UpperLeft()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].UpperLeft()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].UpperLeft()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].UpperLeft()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].LowerLeft() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].LowerLeft()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].LowerLeft()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].LowerLeft()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].LowerLeft()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].LowerLeft()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].UpperRight() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].UpperRight()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].UpperRight()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].UpperRight()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].UpperRight()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].UpperRight()].BaseColor.b;

								SuccessCount++;
							}
						}
					}
					if(CurrentMap->data[i].LowerRight() > -1)
					{
						if(CurrentMap->data[CurrentMap->data[i].LowerRight()].z > CurrentMap->SeaLevel)
						{
							if(CurrentMap->data[CurrentMap->data[i].LowerRight()].z < CurrentMap->MountainLevel)
							{
								TempRed += CurrentMap->data[CurrentMap->data[i].LowerRight()].BaseColor.r;
								TempGreen += CurrentMap->data[CurrentMap->data[i].LowerRight()].BaseColor.g;
								TempBlue += CurrentMap->data[CurrentMap->data[i].LowerRight()].BaseColor.b;

								SuccessCount++;
							}
						}
					}

					if(SuccessCount > 0)
					{
						TempRed /= SuccessCount;
						TempGreen /= SuccessCount;
						TempBlue /= SuccessCount;

						CurrentMap->data[i].BaseColor.r = TempRed;
						CurrentMap->data[i].BaseColor.g = TempGreen;
						CurrentMap->data[i].BaseColor.b = TempBlue;
					}
				}
			}
		}
	}
}

void ProgramManager::EnterMainMenu()
{
	CurrentState = MainMenu;
	///UIMan.MainMenuPanel->show();
}

void ProgramManager::ExitMainMenu()
{
	///UIMan.MainMenuPanel ->hide();
}

void ProgramManager::EnterWorldGenSettings()
{
	CurrentState = WorldGenSetup;
	///UIMan.WGSPanel->show();
	///UIMan.WGSScrollbar->show();
	UpdateWorldGenSettings();
}

void ProgramManager::EnterWorldGen()
{
	CurrentState = WorldGen;
	///UIMan.WGPanel->show();
	WorldGenUIVisible = 1;
	UpdateFloatingTextPosition();
}

void ProgramManager::ExitWorldGen()
{
	///UIMan.WGPanel->hide();
	WorldGenUIVisible = 0;
}

void ProgramManager::ExitWorldGenSettings()
{
	///UIMan.WGSPanel->hide();
	///UIMan.WGSScrollbar->hide();
}

void ProgramManager::ResetWorldGen()
{
	MMan.Reset();
}

void ProgramManager::SetupMapSprite()
{
	MapSprite.setTexture(MapTexture);
	MapSprite.setPosition((MapScaledSize / 4) + 100, 50);
}

void ProgramManager::ScaleMapSprite()
{
	if(MapSpriteScaled == 0)
	{
		MapSprite.scale(MapScaleFactor, MapScaleFactor);
		MapSpriteScaled = 1;
	}
}

void ProgramManager::TileDisplayLoop()
{
	VisibleTileIDList.clear();
	for(int i = 0; i < ((CurrentMap->x * CurrentMap->y) - 1); i++)
	{
		if(CurrentMap->data[i].x <= CurrentMap->data[CurrentCenterTile].x + 1 + HorizontalTileVariation && CurrentMap->data[i].x >= CurrentMap->data[CurrentCenterTile].x - 1 - HorizontalTileVariation)
		{
			if(CurrentMap->data[i].y <= CurrentMap->data[CurrentCenterTile].y + 1 + VerticalTileVariation && CurrentMap->data[i].y >= CurrentMap->data[CurrentCenterTile].y - 1 - VerticalTileVariation)
			{
				VisibleTileIDList.push_back(i);
				TShaderSetBaseColor(i);
				TShaderSetForeColor(i);
				CurrentWindow->draw(CurrentMap->data[i].TileSprite, &TShader.TileShaderOb);
			}
		}
	}
}

void ProgramManager::UpdateTileInfo(int Tile)
{
	TileID.setString(std::to_string(Tile));
	TileBiome.setString(CurrentMap->BiomeToString(Tile));
	TileElevation.setString(std::to_string(CurrentMap->data[Tile].z));
	TileRainfall.setString(std::to_string(CurrentMap->data[Tile].rainfall));
	TileTemperature.setString(std::to_string(CurrentMap->data[Tile].temperature));
}

void ProgramManager::UpdateTileInfo(sf::Vector2f MousePosition)
{
	for(int i = 0; i < VisibleTileIDList.size(); i++)
	{
		sf::FloatRect TileBounds = CurrentMap->data[VisibleTileIDList[i]].TileSprite.getGlobalBounds();

		if(TileBounds.contains(MousePosition))
		{
			UpdateTileInfo(i);
		}
	}
}

void ProgramManager::UpdateTileInfoPosition()
{
	sf::Vector2i TempPosition;
	TempPosition.x = 50;
	TempPosition.y = 50;

	sf::Vector2i TenPixelsDown;
	TenPixelsDown.x = 0;
	TenPixelsDown.y = 10;

	sf::Vector2f FloatTenPixels = CurrentWindow->mapPixelToCoords(TenPixelsDown);

	TileID.setPosition(CurrentWindow->mapPixelToCoords(TempPosition, MapView));

	TempPosition.y += TileID.getGlobalBounds().height + 10;
	TileBiome.setPosition(CurrentWindow->mapPixelToCoords(TempPosition, MapView));

	TempPosition.y += TileBiome.getGlobalBounds().height + 10;
	TileElevation.setPosition(CurrentWindow->mapPixelToCoords(TempPosition, MapView));

	TempPosition.y += TileElevation.getGlobalBounds().height + 10;
	TileRainfall.setPosition(CurrentWindow->mapPixelToCoords(TempPosition, MapView));

	TempPosition.y += TileRainfall.getGlobalBounds().height + 10;
	TileTemperature.setPosition(CurrentWindow->mapPixelToCoords(TempPosition, MapView));
}

void ProgramManager::UpdateFloatingTextPosition()
{
	sf::Vector2i TempPositionText;
	TempPositionText.x = 15;
	TempPositionText.y = 10;

	HelpTip.setPosition(CurrentWindow->mapPixelToCoords(TempPositionText, MapView));
	TempPositionText.x += (CurrentWindow->getSize().x / 3) - 50;
	CurrentInfoOverlay.setPosition(CurrentWindow->mapPixelToCoords(TempPositionText, MapView));
}

void ProgramManager::DisplayWindow()
{
	CurrentWindow->clear();
	if(CurrentState == MainMenu)
	{
		CurrentWindow->draw(BackgroundSprite);
	}
	if(CurrentState == WorldGen)
	{
		if(DisplayState == 1)
		{
			if(UpdateVisibleTileList)
			{
				TileDisplayLoop();
			}
			else
			{
				for(std::vector <int>::iterator CurrentTileID = VisibleTileIDList.begin(); CurrentTileID != VisibleTileIDList.end(); CurrentTileID++)
				{
					CurrentWindow->draw(CurrentMap->data[*CurrentTileID].TileSprite);
				}
			}

			/*UpdateTileInfoPosition();

			CurrentWindow->draw(TileID);
			CurrentWindow->draw(TileBiome);
			CurrentWindow->draw(TileElevation);
			CurrentWindow->draw(TileRainfall);
			CurrentWindow->draw(TileTemperature);*/
		}
		if(DisplayState >= 2)
		{
			CurrentWindow->draw(ProgramManager::MapSprite);
		}
		if(WorldGenUIVisible)
		{
			CurrentWindow->draw(CurrentInfoOverlay);
			CurrentWindow->draw(HelpTip);
		}
	}

	if(CurrentState != WorldGen)
	{
		CurrentWindow->draw(HelpTip);
	}
	UpdateFloatingTextPosition();

	///UIMan.GameGui.draw();//******************************//
	CurrentWindow->display();
}

void ProgramManager::ToggleWorldGenVisibility()
{
	if(WorldGenUIVisible == 0)
	{
		///UIMan.WGPanel->show();
		WorldGenUIVisible = 1;
	}
	else if(WorldGenUIVisible == 1)
	{
		///UIMan.WGPanel->hide();
		WorldGenUIVisible = 0;
	}
}

void ProgramManager::Draw()
{
	if(CurrentState == WorldGen)
	{
		if(DisplayState == 1)
		{
			DrawTiles();
			if(DoBlendTileBackgrounds)
			{
				BlendTileBackgrounds();
			}
		}
		if(DisplayState == 2)
		{
			DrawBiomeMap();
			if(DoBlendBiomeMap)
			{
				BlendBiomeColors();
			}
		}
		if(DisplayState == 3)
		{
			DrawHeightMap(0);
		}
		if(DisplayState == 4)
		{
			DrawTemperatureMap(0);
		}
		if(DisplayState == 5)
		{
			DrawRainfallMap(1, 1);
		}
		if(DisplayState == 6)
		{
			DrawHeightRegionMap();
		}
		if(DisplayState == 7)
		{
			DrawWaterRegionMap();
		}
		if(DisplayState == 8)
		{
			DrawRegionMap();
		}
	}
	if(CurrentState == WorldMap)
	{
		DrawTiles();
	}
}

void ProgramManager::ProcessKey(int Key)
{
	if(Key == sf::Keyboard::Q || Key == sf::Keyboard::E)//q = 16 // e = 4 // 71 = left // 72 = right // 73 = up // 74 = down
	{
		if(CurrentState == WorldGen)
		{
			ChangeDisplayState(Key);
		}
	}
	if(Key >= sf::Keyboard::Left && Key <= sf::Keyboard::Down)
	{
		if(CurrentState == WorldGen || CurrentState == WorldMap)
		{
			UpdateMapView(Key);
		}
	}
	if(Key == sf::Keyboard::R)
	{
		if(CurrentState == WorldGen)
		{
			ResetWorldGen();
			CommenceWorldGen();
		}
	}
	if(Key == sf::Keyboard::Tab)
	{
		if(CurrentState == WorldGen)
		{
			ToggleWorldGenVisibility();
		}
	}
	if (Key == sf::Keyboard::Return)
	{
		if (CurrentState == MainMenu)
		{
			EnterWorldGen();
		}
	}
}

void ProgramManager::UpdateMapView(int Key)
{
	int NewX = CurrentMap->data[CurrentCenterTile].x;
	int NewY = CurrentMap->data[CurrentCenterTile].y;
	int MapSize = (CurrentMap->x * CurrentMap->y) - 1;

	if(Key == 71)
	{
		if(CurrentMap->ConvertToAbsolute(NewX - MapMoveDelta, NewY) <= MapSize && CurrentMap->ConvertToAbsolute(NewX - MapMoveDelta, NewY) >= 0)
		{
			CurrentCenterTile = CurrentMap->ConvertToAbsolute(NewX - MapMoveDelta, NewY);
		}
	}
	if(Key == 72)
	{
		if(CurrentMap->ConvertToAbsolute(NewX + MapMoveDelta, NewY) <= MapSize && CurrentMap->ConvertToAbsolute(NewX + MapMoveDelta, NewY) >= 0)
		{
			CurrentCenterTile = CurrentMap->ConvertToAbsolute(NewX + MapMoveDelta, NewY);
		}
	}
	if(Key == 73)
	{
		if(CurrentMap->ConvertToAbsolute(NewX, NewY - MapMoveDelta) <= MapSize && CurrentMap->ConvertToAbsolute(NewX, NewY - MapMoveDelta) >= 0)
		{
			CurrentCenterTile = CurrentMap->ConvertToAbsolute(NewX, NewY - MapMoveDelta);
		}
	}
	if(Key == 74)
	{
		if(CurrentMap->ConvertToAbsolute(NewX, NewY + MapMoveDelta) <= MapSize && CurrentMap->ConvertToAbsolute(NewX, NewY + MapMoveDelta) >= 0)
		{
			CurrentCenterTile = CurrentMap->ConvertToAbsolute(NewX, NewY + MapMoveDelta);
		}
	}
	MapView.setCenter(CurrentMap->data[CurrentCenterTile].WindowX, CurrentMap->data[CurrentCenterTile].WindowY + 20);
}

void ProgramManager::ChangeDisplayState(int Key)
{
	if(Key == 16)
	{
		if(DisplayState == 1)
		{
			DisplayState = 8;
		}
		else if(DisplayState > 1)
		{
			DisplayState--;
		}
	}
	if(Key == 4)
	{
		if(DisplayState == 8)
		{
			DisplayState = 1;
		}
		else if(DisplayState < 8)
		{
			DisplayState++;
		}
	}
	if(DisplayState != 1)
	{
		MapView.setCenter(0, 0);
		sf::Vector2i Pos;
		Pos.x = (MapScaledSize / 4) + 100;
		Pos.y = 50;
		sf::Vector2f NewPos = CurrentWindow->mapPixelToCoords(Pos);
		MapSprite.setPosition(NewPos);
	}
	if(DisplayState == 1)
	{
		CurrentWindow->setView(MapView);
		SetBaseCenterTile();
	}
	if(Key == -1)
	{
		DisplayState = 1;
		MapView.setSize(WindowWidth, WindowHeight);
		CurrentWindow->setView(MapView);
		SetBaseCenterTile();
	}
	//UpdateFloatingTextPosition();
	UpdateOverlayName();
	Draw();
}

void ProgramManager::UpdateOverlayName()
{
	if(DisplayState == 1)
	{
		CurrentInfoOverlay.setString("Tiled Biome Map");
	}
	else if(DisplayState == 2)
	{
		CurrentInfoOverlay.setString("Biome Map");
	}
	else if(DisplayState == 3)
	{
		CurrentInfoOverlay.setString("Elevation Map");
	}
	else if(DisplayState == 4)
	{
		CurrentInfoOverlay.setString("Temperature Map");
	}
	else if(DisplayState == 5)
	{
		CurrentInfoOverlay.setString("Rainfall Map");
	}
	else if(DisplayState == 6)
	{
		CurrentInfoOverlay.setString("Height Region Map");
	}
	else if(DisplayState == 7)
	{
		CurrentInfoOverlay.setString("Water Region Map");
	}
	else if(DisplayState == 8)
	{
		CurrentInfoOverlay.setString("Biome Region Map");
	}
}

void ProgramManager::AdjustZoom(int Direction)
{
	if(Direction == 1)
	{
		if(ViewDelta - .2 >= ViewMinimum)
		{
			MapView.zoom(ZoomInDelta);
			ViewDelta += (-1 + ZoomInDelta);
			DisplayWindow();
		}
	}
	if(Direction == -1)
	{
		MapView.zoom(ZoomOutDelta);
		ViewDelta += (-1 + ZoomOutDelta);
		DisplayWindow();
	}
	UpdateVisibleTiles();
}
void ProgramManager::SetTileWindowPositions()
{
	if(CurrentState == WorldGen || CurrentState == WorldMap)
	{
		for(int i = 0; i < (CurrentMap->x * CurrentMap->y) - 1; i++)
		{
			CurrentMap->data[i].WindowX = CurrentMap->data[i].x * TilesXSize;
			CurrentMap->data[i].WindowY = CurrentMap->data[i].y * TilesYSize;
		}
	}
}

void ProgramManager::DrawTiles()
{
	int MapSizeX = CurrentMap->x;
	int MapSizeY = CurrentMap->y;
	int MapSizeTotal = (MapSizeX * MapSizeY) - 1;

	sf::Color TempColor;
	TempColor.r = 255;
	TempColor.g = 255;
	TempColor.b = 255;
	TempColor.a = 255;

	sf::Color TundraColor;
	TundraColor.r = 89;
	TundraColor.g = 141;
	TundraColor.b = 232;
	TundraColor.a = 255;

	sf::Color SnowColor;
	SnowColor.r = 151;//206//233//193
	SnowColor.g = 235;//199//226
	SnowColor.b = 255;//194//221
	SnowColor.a = 255;

	sf::Color MountainSnowColor;
	MountainSnowColor.r = 233;//206//233//193
	MountainSnowColor.g = 226;//199//226
	MountainSnowColor.b = 221;//194//221
	MountainSnowColor.a = 255;

	sf::Color DesertColor;
	DesertColor.r = 188;
	DesertColor.g = 146;
	DesertColor.b = 103;
	DesertColor.a = 255;

	sf::Color GrasslandColor;
	GrasslandColor.r = 157;//129 129 90
	GrasslandColor.g = 133; //91 92 58
	GrasslandColor.b = 75;
	GrasslandColor.a = 255;

	sf::Color ForestColor;
	ForestColor.r = 50;
	ForestColor.g = 60;
	ForestColor.b = 20;
	ForestColor.a = 255;

	sf::Color MarshColor;
	MarshColor.r = 94;
	MarshColor.g = 101;
	MarshColor.b = 78;
	MarshColor.a = 255;

	sf::Color TForestColor;
	TForestColor.r = 43;
	TForestColor.g = 46;
	TForestColor.b = 43;
	TForestColor.a = 255;

	sf::Color RainforestColor;
	RainforestColor.r = 43;
	RainforestColor.g = 46;
	RainforestColor.b = 43;
	RainforestColor.a = 255;

	sf::Color BareColor;
	BareColor.r = 171;//76
	BareColor.g = 166;//71
	BareColor.b = 163;//68
	BareColor.a = 255;

	sf::Color ScorchedColor;
	ScorchedColor.r = 83;
	ScorchedColor.g = 83;
	ScorchedColor.b = 83;
	ScorchedColor.a = 255;

	sf::Color TaigaColor;
	TaigaColor.r = 80;
	TaigaColor.g = 96;
	TaigaColor.b = 60;
	TaigaColor.a = 255;

	sf::Color IceColor;
	IceColor.r = 30;
	IceColor.g = 151;
	IceColor.b = 162;
	IceColor.a = 255;

	sf::Color SavannahColor;
	SavannahColor.r = 165;
	SavannahColor.g = 121;
	SavannahColor.b = 56;
	SavannahColor.a = 255;

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

	int Pos = 0;

	while(Pos <= MapSizeTotal)
	{
		if(CurrentMap->data[Pos].Biome == 0)
		{
			CurrentMap->data[Pos].TileID = 0;
			if(CurrentMap->data[Pos].z <= CurrentMap->SeaLevel)
			{
				CurrentMap->data[Pos].BaseColor.r = WaterColor.r;
				CurrentMap->data[Pos].BaseColor.g = WaterColor.g;
				CurrentMap->data[Pos].BaseColor.b = WaterColor.b + CurrentMap->data[Pos].z;

				CurrentMap->data[Pos].ForeColor.r = WaterColor.r;
				CurrentMap->data[Pos].ForeColor.g = WaterColor.g;
				CurrentMap->data[Pos].ForeColor.b = WaterColor.b + CurrentMap->data[Pos].z;

				CurrentMap->data[Pos].HasForeground = 0;
				CurrentMap->data[Pos].TileID = 0;

				if(ForceGlyphsOnAll)
				{
					CurrentMap->data[Pos].HasForeground = 1;
					CurrentMap->data[Pos].TileID = 5;
				}
			}
			if(CurrentMap->data[Pos].IsRiver == 1)
			{
				if(CurrentMap->data[Pos].z < CurrentMap->MountainLevel)
				{
					CurrentMap->SetRiverBaseColor(Pos);

					CurrentMap->data[Pos].ForeColor.r = 81;
					CurrentMap->data[Pos].ForeColor.g = 113;
					CurrentMap->data[Pos].ForeColor.b = 167;
					CurrentMap->data[Pos].TileID = CurrentMap->GetRiverDirection(Pos);

					CurrentMap->data[Pos].HasForeground = 1;
				}
			}
			if(DisplayRiverStartPoints)
			{
				if(CurrentMap->data[Pos].IsRiverStartPoint == 1)
				{
					CurrentMap->data[Pos].BaseColor.r = 255;
					CurrentMap->data[Pos].BaseColor.g = 0;
					CurrentMap->data[Pos].BaseColor.b = 0;

					CurrentMap->data[Pos].HasForeground = 0;
					CurrentMap->data[Pos].TileID = 0;
				}
			}
			if(CurrentMap->data[Pos].z > CurrentMap->SeaLevel && CurrentMap->data[Pos].IsRiver == 0)
			{
				CurrentMap->data[Pos].BaseColor.r = CurrentMap->data[Pos].z;
				CurrentMap->data[Pos].BaseColor.g = CurrentMap->data[Pos].z;
				CurrentMap->data[Pos].BaseColor.b = CurrentMap->data[Pos].z;

				CurrentMap->data[Pos].HasForeground = 0;
				CurrentMap->data[Pos].TileID = 0;
			}
		}
		if(CurrentMap->data[Pos].Biome == 1)
		{
			CurrentMap->data[Pos].BaseColor.r = TundraColor.r;
			CurrentMap->data[Pos].BaseColor.g = TundraColor.g + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);
			CurrentMap->data[Pos].BaseColor.b = TundraColor.b;

			CurrentMap->data[Pos].ForeColor.r = TundraColor.r;
			CurrentMap->data[Pos].ForeColor.g = TundraColor.g;
			CurrentMap->data[Pos].ForeColor.b = TundraColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;
		}
		else if(CurrentMap->data[Pos].Biome == 2)
		{
			int GreenChange = (255 - SnowColor.g) / (CurrentMap->MountainLevel - CurrentMap->SeaLevel);
			if(CurrentMap->data[Pos].z >= CurrentMap->MountainLevel)
			{
				CurrentMap->data[Pos].BaseColor.r = BareColor.r - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;//MountainSnowColor.r - (CurrentMap->data[Pos].z - CurrentMap->SnowLevel - 1);
				CurrentMap->data[Pos].BaseColor.g = BareColor.g - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;//MountainSnowColor.g - (CurrentMap->data[Pos].z - CurrentMap->SnowLevel - 1);
				CurrentMap->data[Pos].BaseColor.b = BareColor.b - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;//MountainSnowColor.b - (CurrentMap->data[Pos].z - CurrentMap->SnowLevel - 1);

				if(CurrentMap->IsDeepMountain(Pos) == 0)
				{
					// CurrentMap->SetMountainBaseColor(Pos);
				}

				CurrentMap->data[Pos].ForeColor.r = MountainSnowColor.r;
				CurrentMap->data[Pos].ForeColor.g = MountainSnowColor.g;
				CurrentMap->data[Pos].ForeColor.b = MountainSnowColor.b;

				CurrentMap->data[Pos].TileID = 1;

				CurrentMap->data[Pos].HasForeground = 1;
			}
			else
			{
				CurrentMap->data[Pos].BaseColor.r = SnowColor.r + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel - 1);
				CurrentMap->data[Pos].BaseColor.g = SnowColor.g + ((CurrentMap->data[Pos].z - CurrentMap->SeaLevel - 1) * GreenChange);
				CurrentMap->data[Pos].BaseColor.b = SnowColor.b;// + (CurrentMap->data[TempArrayPos].z - CurrentMap->SeaLevel - 1);
				CurrentMap->data[Pos].BaseColor.a = 255;

				CurrentMap->data[Pos].ForeColor.r = SnowColor.r;
				CurrentMap->data[Pos].ForeColor.g = SnowColor.g;
				CurrentMap->data[Pos].ForeColor.b = SnowColor.b;

				CurrentMap->data[Pos].TileID = 0;

				CurrentMap->data[Pos].HasForeground = 0;
			}

		}
		else if(CurrentMap->data[Pos].Biome == 3)
		{
			CurrentMap->data[Pos].BaseColor.r = DesertColor.r + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);
			CurrentMap->data[Pos].BaseColor.g = DesertColor.g + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);
			CurrentMap->data[Pos].BaseColor.b = DesertColor.b + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);

			CurrentMap->data[Pos].ForeColor.r = DesertColor.r;
			CurrentMap->data[Pos].ForeColor.g = DesertColor.g;
			CurrentMap->data[Pos].ForeColor.b = DesertColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;

			if(ForceGlyphsOnAll)
			{
				CurrentMap->data[Pos].HasForeground = 1;
				CurrentMap->data[Pos].TileID = 5;
			}
		}
		else if(CurrentMap->data[Pos].Biome == 4)
		{
			CurrentMap->data[Pos].BaseColor.r = GrasslandColor.r + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel) / 3;
			CurrentMap->data[Pos].BaseColor.g = GrasslandColor.g + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel) / 1.25;
			CurrentMap->data[Pos].BaseColor.b = GrasslandColor.b;

			CurrentMap->data[Pos].ForeColor.r = GrasslandColor.r;
			CurrentMap->data[Pos].ForeColor.g = GrasslandColor.g;
			CurrentMap->data[Pos].ForeColor.b = GrasslandColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;

			if(ForceGlyphsOnAll)
			{
				CurrentMap->data[Pos].HasForeground = 1;
				CurrentMap->data[Pos].TileID = 6;
			}
		}
		else if(CurrentMap->data[Pos].Biome == 5)
		{
			CurrentMap->data[Pos].BaseColor.r = ForestColor.r;
			CurrentMap->data[Pos].BaseColor.g = ForestColor.g + CurrentMap->data[Pos].z - CurrentMap->SeaLevel;
			CurrentMap->data[Pos].BaseColor.b = ForestColor.b;

			CurrentMap->data[Pos].ForeColor.r = ForestColor.r;
			CurrentMap->data[Pos].ForeColor.g = ForestColor.g;
			CurrentMap->data[Pos].ForeColor.b = ForestColor.b;

			CurrentMap->data[Pos].TileID = 2;

			CurrentMap->data[Pos].HasForeground = 0;
		}
		else if(CurrentMap->data[Pos].Biome == 6)
		{
			CurrentMap->data[Pos].BaseColor.r = MarshColor.r - (CurrentMap->data[Pos].z - CurrentMap->SeaLevel) * .5;
			CurrentMap->data[Pos].BaseColor.g = MarshColor.g;
			CurrentMap->data[Pos].BaseColor.b = MarshColor.b - (CurrentMap->data[Pos].z - CurrentMap->SeaLevel) * .5;

			CurrentMap->data[Pos].ForeColor.r = MarshColor.r;
			CurrentMap->data[Pos].ForeColor.g = MarshColor.g;
			CurrentMap->data[Pos].ForeColor.b = MarshColor.b;

			CurrentMap->data[Pos].TileID = 0;

			CurrentMap->data[Pos].HasForeground = 0;
		}
		else if(CurrentMap->data[Pos].Biome == 7)
		{
			CurrentMap->data[Pos].BaseColor.r = TForestColor.r;
			CurrentMap->data[Pos].BaseColor.g = TForestColor.g + CurrentMap->data[Pos].z - CurrentMap->SeaLevel;
			CurrentMap->data[Pos].BaseColor.b = TForestColor.b;

			CurrentMap->data[Pos].ForeColor.r = TForestColor.r;
			CurrentMap->data[Pos].ForeColor.g = TForestColor.g;
			CurrentMap->data[Pos].ForeColor.b = TForestColor.b;

			CurrentMap->data[Pos].TileID = 0;
		}
		else if(CurrentMap->data[Pos].Biome == 8)
		{
			CurrentMap->data[Pos].BaseColor.r = RainforestColor.r;
			CurrentMap->data[Pos].BaseColor.g = RainforestColor.g + CurrentMap->data[Pos].z - CurrentMap->SeaLevel;
			CurrentMap->data[Pos].BaseColor.b = RainforestColor.b;

			CurrentMap->data[Pos].ForeColor.r = RainforestColor.r;
			CurrentMap->data[Pos].ForeColor.g = RainforestColor.g;
			CurrentMap->data[Pos].ForeColor.b = RainforestColor.b;

			CurrentMap->data[Pos].TileID = 3;

			CurrentMap->data[Pos].HasForeground = 1;
		}
		else if(CurrentMap->data[Pos].Biome == 9)
		{
			CurrentMap->data[Pos].BaseColor.r = BareColor.r - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;
			CurrentMap->data[Pos].BaseColor.g = BareColor.g - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;
			CurrentMap->data[Pos].BaseColor.b = BareColor.b - CurrentMap->data[Pos].z - CurrentMap->MountainLevel - 1;

			if(CurrentMap->IsDeepMountain(Pos) == 0)
			{
				//CurrentMap->SetMountainBaseColor(Pos);
			}

			CurrentMap->data[Pos].ForeColor.r = BareColor.r;
			CurrentMap->data[Pos].ForeColor.g = BareColor.g;
			CurrentMap->data[Pos].ForeColor.b = BareColor.b;

			CurrentMap->data[Pos].TileID = 1;

			CurrentMap->data[Pos].HasForeground = 1;
		}
		else if(CurrentMap->data[Pos].Biome == 10)
		{
			CurrentMap->data[Pos].BaseColor.r = ScorchedColor.r + CurrentMap->data[Pos].z - 199;
			CurrentMap->data[Pos].BaseColor.g = ScorchedColor.g + CurrentMap->data[Pos].z - 199;
			CurrentMap->data[Pos].BaseColor.b = ScorchedColor.b + CurrentMap->data[Pos].z - 199;

			if(CurrentMap->IsDeepMountain(Pos) == 0)
			{
				//CurrentMap->SetMountainBaseColor(Pos);
			}

			CurrentMap->data[Pos].ForeColor.r = ScorchedColor.r;
			CurrentMap->data[Pos].ForeColor.g = ScorchedColor.g;
			CurrentMap->data[Pos].ForeColor.b = ScorchedColor.b;

			CurrentMap->data[Pos].TileID = 1;

			CurrentMap->data[Pos].HasForeground = 1;
		}
		else if(CurrentMap->data[Pos].Biome == 11)
		{
			CurrentMap->data[Pos].BaseColor.r = WaterColor.r;
			CurrentMap->data[Pos].BaseColor.g = WaterColor.g;
			CurrentMap->data[Pos].BaseColor.b = WaterColor.b + CurrentMap->data[Pos].z;

			CurrentMap->data[Pos].ForeColor.r = WaterColor.r;
			CurrentMap->data[Pos].ForeColor.g = WaterColor.g;
			CurrentMap->data[Pos].ForeColor.b = WaterColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;

			if(ForceGlyphsOnAll)
			{
				CurrentMap->data[Pos].HasForeground = 1;
				CurrentMap->data[Pos].TileID = 5;
			}
		}
		else if(CurrentMap->data[Pos].Biome == 12)
		{
			CurrentMap->data[Pos].BaseColor.r = TaigaColor.r;
			CurrentMap->data[Pos].BaseColor.g = TaigaColor.g;
			CurrentMap->data[Pos].BaseColor.b = TaigaColor.b + CurrentMap->data[Pos].z;

			CurrentMap->data[Pos].ForeColor.r = TaigaColor.r;
			CurrentMap->data[Pos].ForeColor.g = TaigaColor.g;
			CurrentMap->data[Pos].ForeColor.b = TaigaColor.b;

			CurrentMap->data[Pos].TileID = 0;

			CurrentMap->data[Pos].HasForeground = 1;
		}
		else if(CurrentMap->data[Pos].Biome == 13)
		{
			CurrentMap->data[Pos].BaseColor.r = IceColor.r;
			CurrentMap->data[Pos].BaseColor.g = IceColor.g;
			CurrentMap->data[Pos].BaseColor.b = IceColor.b + CurrentMap->data[Pos].z;

			CurrentMap->data[Pos].ForeColor.r = IceColor.r;
			CurrentMap->data[Pos].ForeColor.g = IceColor.g;
			CurrentMap->data[Pos].ForeColor.b = IceColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;
		}
		else if(CurrentMap->data[Pos].Biome == 14)
		{
			CurrentMap->data[Pos].BaseColor.r = SavannahColor.r + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);
			CurrentMap->data[Pos].BaseColor.g = SavannahColor.g + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);
			CurrentMap->data[Pos].BaseColor.b = SavannahColor.b + (CurrentMap->data[Pos].z - CurrentMap->SeaLevel);

			CurrentMap->data[Pos].ForeColor.r = SavannahColor.r;
			CurrentMap->data[Pos].ForeColor.g = SavannahColor.g;
			CurrentMap->data[Pos].ForeColor.b = SavannahColor.b;

			CurrentMap->data[Pos].HasForeground  = 0;
			CurrentMap->data[Pos].TileID = 0;

			if(ForceGlyphsOnAll)
			{
				CurrentMap->data[Pos].HasForeground = 1;
				CurrentMap->data[Pos].TileID = 5;
			}
		}

		if(CurrentMap->data[Pos].IsRiver == 1)
		{
			if(CurrentMap->data[Pos].z < CurrentMap->MountainLevel)
			{
				CurrentMap->SetRiverBaseColor(Pos);

				CurrentMap->data[Pos].ForeColor.r = 81;
				CurrentMap->data[Pos].ForeColor.g = 113;
				CurrentMap->data[Pos].ForeColor.b = 167;

				CurrentMap->data[Pos].TileID = CurrentMap->GetRiverDirection(Pos);

				CurrentMap->data[Pos].HasForeground = 1;

				if(ForceGlyphsOnAll)
				{
					CurrentMap->data[Pos].HasForeground = 1;
					CurrentMap->data[Pos].TileID = 5;
				}
			}

		}
		if(DisplayRiverStartPoints)
		{
			if(CurrentMap->data[Pos].IsRiverStartPoint == 1)
			{
				CurrentMap->data[Pos].BaseColor.r = 255;
				CurrentMap->data[Pos].BaseColor.g = 0;
				CurrentMap->data[Pos].BaseColor.b = 0;

				CurrentMap->data[Pos].HasForeground  = 0;
				CurrentMap->data[Pos].TileID = 0;
			}
		}
		Pos++;
	}
	Pos = 0;//Set Tile Positions and setup sprites here.
	while(Pos <= MapSizeTotal)
	{
		CurrentMap->data[Pos].TileSprite.setTexture(CurrentTileset.TilesetTexture);
		CurrentMap->data[Pos].TileSprite.setTextureRect(CurrentTileset.GetCellBounds(CurrentMap->data[Pos].TileID));
		CurrentMap->data[Pos].TileSprite.setPosition(CurrentMap->data[Pos].WindowX, CurrentMap->data[Pos].WindowY);

		Pos++;
	}
	UpdateMapView(-1);
}

void ProgramManager::TShaderSetBaseColor(int Tile)
{
	TShader.BaseColor.r = CurrentMap->data[Tile].BaseColor.r;
	TShader.BaseColor.g = CurrentMap->data[Tile].BaseColor.g;
	TShader.BaseColor.b = CurrentMap->data[Tile].BaseColor.b;

	TShader.UpdateVariables();
}

void ProgramManager::TShaderSetForeColor(int Tile)
{
	TShader.ForeColor.r = CurrentMap->data[Tile].ForeColor.r;
	TShader.ForeColor.g = CurrentMap->data[Tile].ForeColor.g;
	TShader.ForeColor.b = CurrentMap->data[Tile].ForeColor.b;

	TShader.UpdateVariables();
}

void ProgramManager::ProcessSignal(int SignalID)
{
	if (SignalID == 1)
	{
		ExitMainMenu();
		MMan.SetAsDefault();
		EnterWorldGen();
		CommenceWorldGen();
	}
	if (SignalID == 2)
	{
		ExitMainMenu();
		EnterWorldGenSettings();
	}
	if (SignalID == 3)
	{
		CurrentWindow->close();
	}
	if (SignalID == 4)
	{
		SetWorldGenSettings();
		ExitWorldGenSettings();
		EnterWorldGen();
		CommenceWorldGen();
	}
	if (SignalID == 5)
	{
		ExitWorldGenSettings();
		EnterMainMenu();
	}
	if (SignalID == 6)
	{
		MMan.SetAsDefault();
		UpdateWorldGenSettings();
	}
	if (SignalID == 7)
	{
		ResetWorldGen();
		ExitWorldGen();
		EnterMainMenu();
	}
	if (SignalID == 8)
	{
		ResetWorldGen();
		ExitWorldGen();
		EnterWorldGenSettings();
	}
	if (SignalID == 9)
	{
		ResetWorldGen();
		CommenceWorldGen();
	}
	if (SignalID == 10)
	{
		//Open Settings Menu
	}
	if (SignalID == 11)
	{
		ChangeDisplayState(16);
	}
	if (SignalID == 12)
	{
		ChangeDisplayState(4);
	}
	if (SignalID == 13)
	{
		//Load from file, open dialog.
	}
	if (SignalID == 14)
	{
		//Save to file, ask for name.
	}
}

void ProgramManager::UpdateShaderVariables(int ArrayXSize, int TileID)
{
	TShader.ArrayXSize = ArrayXSize;
	TShader.TileID = TileID;
	TShader.TileXSize = TilesXSize;
	TShader.TileYSize = TilesYSize;
	TShader.UpdateShaderVariables();
}

void ProgramManager::TShaderSetTexture(sf::Texture CurrentTexture)
{
	TShader.TileTexture = &CurrentTexture;
}

void ProgramManager::StartStateManager()
{
	BaseReplaceColor.r = 255;
	BaseReplaceColor.g = 0;
	BaseReplaceColor.b = 255;

	ForeReplaceColor.r = 255;
	ForeReplaceColor.g = 255;
	ForeReplaceColor.b = 255;

	GlobalFont.loadFromFile(FontLocation);

	TileID.setFont(GlobalFont);
	TileBiome.setFont(GlobalFont);
	TileElevation.setFont(GlobalFont);
	TileRainfall.setFont(GlobalFont);
	TileTemperature.setFont(GlobalFont);

	TileID.setCharacterSize(12);
	TileBiome.setCharacterSize(12);
	TileElevation.setCharacterSize(12);
	TileRainfall.setCharacterSize(12);
	TileTemperature.setCharacterSize(12);

	CurrentInfoOverlay.setFont(GlobalFont);
	CurrentInfoOverlay.setCharacterSize(14);
	UpdateOverlayName();

	CurrentTileset.ConfigureTileset(TilesetLoc, 16, 16, 160, 160);
	TShader.ConfigureShaders();
	TShaderSetTexture(CurrentTileset.TilesetTexture);

	CurrentState = MainMenu;

	MenuBackgroundTexture.loadFromFile("Background2.png");
	BackgroundSprite.setTexture(MenuBackgroundTexture);

	//UIMan.MainSettingsPanel->hide();
	///UIMan.WGSPanel->hide();
	///UIMan.WGSScrollbar->hide();
	//UIMan.WGPanel->hide();

	/*WorldName = TempWorldName + tgui::to_string(CurrentWorldNameCount);

	if(FileExists(Slash + WorldName + End) == 1)
	{
		while(FileExists(Slash + WorldName + End) == 1)
		{
			WorldName = TempWorldName + tgui::to_string(CurrentWorldNameCount);
			CurrentWorldNameCount++;
		}
	}
	if(FileExists(Slash + WorldName + End) == 0)
	{
		UIMan.WGSProfileName->setText(WorldName);
	}*/
}

void ProgramManager::SetBaseCenterTile()
{
	MapView.setSize(WindowWidth, WindowHeight);
	sf::Vector2i ZeroXY(0, 0);
	sf::Vector2i WindowX(WindowWidth, 0);
	sf::Vector2i WindowY(0, WindowHeight);

	sf::Vector2f ZeroPos = CurrentWindow->mapPixelToCoords(ZeroXY, MapView);
	sf::Vector2f XSize = CurrentWindow->mapPixelToCoords(WindowX, MapView);
	sf::Vector2f YSize = CurrentWindow->mapPixelToCoords(WindowY, MapView);

	WidthInTiles = (XSize.x - ZeroPos.x) / TilesXSize;
	HeightInTiles = (YSize.y - ZeroPos.y) / TilesYSize;

	HorizontalTileVariation = WidthInTiles / 2;
	VerticalTileVariation = HeightInTiles / 2;

	CurrentCenterTile = CurrentMap->ConvertToAbsolute(WidthInTiles / 2, HeightInTiles / 2);
}

void ProgramManager::UpdateVisibleTiles()
{
	sf::Vector2i ZeroXY(0, 0);
	sf::Vector2i WindowX(WindowWidth, 0);
	sf::Vector2i WindowY(0, WindowHeight);

	sf::Vector2f ZeroPos = CurrentWindow->mapPixelToCoords(ZeroXY, MapView);
	sf::Vector2f XSize = CurrentWindow->mapPixelToCoords(WindowX, MapView);
	sf::Vector2f YSize = CurrentWindow->mapPixelToCoords(WindowY, MapView);

	WidthInTiles = (XSize.x - ZeroPos.x) / TilesXSize;
	HeightInTiles = (YSize.y - ZeroPos.y) / TilesYSize;

	HorizontalTileVariation = WidthInTiles / 2;
	VerticalTileVariation = HeightInTiles / 2;
}

void ProgramManager::CommenceWorldGen()
{
	TileShadeOn();
	//AdjustMapImageSize();
	///UIMan.WGListBox->removeAllItems();

	float TotalTime = 0.00;

	std::string seconds = " seconds";
	std::string printout;
	std::string temp;

	sf::Color TempColor;
	TempColor.r = 255;
	TempColor.g = 255;
	TempColor.b = 255;
	TempColor.a = 255;

	CurrentMap = &MMan.MainMap;
	CurrentWRM = &MMan.MainWRM;
	CurrentHRM = &MMan.MainHRM;

	MMan.Initialize();
	MapImage.create(CurrentMap->x, CurrentMap->y, TempColor);
	ScaleMapSprite();

	///UIMan.WGProgressBar->setMaximum(13);//EDIT IF STEPS ADDED OR REMOVED.
	///UIMan.WGProgressBar->setValue(0);

	sf::Clock FunctionTime;
	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Generating height map.");
	DisplayWindow();
	MMan.MainMap.GenerateHeightMap();

	SetTileWindowPositions();//Set positions for tiles since this is the first point at which they exist.

	Draw();
	DisplayMap = 1;
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Height map generation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	if(MMan._HeightTurbulence == 1)
	{
		FunctionTime.restart();
		///UIMan.WGProgressBar->setText("Applying turbulence to height map.");
		DisplayWindow();
		MMan.MainMap.Turbulence();
		Draw();
		SetupMapSprite();
		FunctionSeconds = FunctionTime.getElapsedTime();
		temp = "Height Turbulence Time: ";
		///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
		///UIMan.WGListBox->addItem(printout);
		TotalTime += FunctionSeconds.asSeconds();
	}
	else if(MMan._HeightTurbulence == 0)
	{
		///UIMan.WGProgressBar->incrementValue();
		printout = "Height turbulence skipped.";
		///UIMan.WGListBox->addItem(printout);
	}
	///UIMan.WGProgressBar->incrementValue();

	if(MMan._DoMapSmoothing == 1)//COMBINE INTO SINGLE SMOOTHING VARIABLE/ACTION
	{
		FunctionTime.restart();
		///UIMan.WGProgressBar->setText("Smoothing map.");
		DisplayWindow();
		MMan.MainMap.SmoothNoise(0);
		Draw();
		SetupMapSprite();
		FunctionSeconds = FunctionTime.getElapsedTime();
		temp = "Map Smoothing Time: ";
		///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
		///UIMan.WGListBox->addItem(printout);
		TotalTime += FunctionSeconds.asSeconds();
	}
	else if(MMan._DoMapSmoothing == 0)
	{
		///UIMan.WGProgressBar->incrementValue();
		printout = "Map smoothing skipped.";
		///UIMan.WGListBox->addItem(printout);
	}
	///UIMan.WGProgressBar->incrementValue();

	if(MMan._DoMapSideSmoothing == 1)
	{
		FunctionTime.restart();
		///UIMan.WGProgressBar->setText("Smoothing map sides.");
		DisplayWindow();
		MMan.MainMap.SmoothNoiseOutside(0);
		MMan.MainMap.SmoothNoiseOutside(0);
		SetupMapSprite();
		FunctionSeconds = FunctionTime.getElapsedTime();
		temp = "Map Side Smoothing Time: ";
		///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
		///UIMan.WGListBox->addItem(printout);
		TotalTime += FunctionSeconds.asSeconds();
	}
	else if(MMan._DoMapSideSmoothing == 0)
	{
		///UIMan.WGProgressBar->incrementValue();
		printout = "Map side smoothing skipped.";
		///UIMan.WGListBox->addItem(printout);
	}
	///UIMan.WGProgressBar->incrementValue();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Flattening small water bodies.");
	DisplayWindow();
	MMan.MainWRM.CalculateWaterRegions(0);
	MMan.MainWRM.FlattenSmallWaterBodies();
	MMan.MainWRM.ClearWaterRegions();
	MMan.MainWRM.CalculateWaterRegions(0);
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Small water body flattening time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Generating rivers.");
	DisplayWindow();
	MMan.MainRM.GenerateRivers(0);
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "River generation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Calculating height regions.");
	DisplayWindow();
	MMan.MainHRM.CalculateHeightRegions(0);//Threadable
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Height region calculation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Generating temperature map.");
	DisplayWindow();
	MMan.MainMap.GenerateTemperatureMap();//Threadable
	MMan.MainMap.ApplyNoiseToTemperature();
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Temperature map generation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Generating rainshadow.");
	DisplayWindow();

	MMan.MainMap.CalculateRainShadow(0);//Threadable
	MMan.MainMap.SmoothRainfall();
	MMan.MainMap.ApplyNoiseToRainfall(0);
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Rainshadow generation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	/*FunctionTime.restart();
	UIMan.WGProgressBar->setText("Propagating water rainfall.");
	DisplayWindow();
	//MMan.MainMap.CalculateMapRainfall(0);

	Draw();
	UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Rainfall propagation time: ";
	printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	UIMan.WorldGenLogBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();*/

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Setting tile biomes.");
	DisplayWindow();
	MMan.MainMap.SetTileBiomes();
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();
	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Biome determination time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	FunctionTime.restart();
	///UIMan.WGProgressBar->setText("Calculating Map regions.");
	DisplayWindow();
	MMan.MainMap.CalculateMapRegions(0);
	Draw();
	///UIMan.WGProgressBar->incrementValue();
	SetupMapSprite();

	FunctionSeconds = FunctionTime.getElapsedTime();
	temp = "Map region calculation time: ";
	///printout = temp + (tgui::to_string(FunctionSeconds.asSeconds())) + seconds;
	///UIMan.WGListBox->addItem(printout);
	TotalTime += FunctionSeconds.asSeconds();

	temp = "Total generation time: ";
	///printout = temp + (tgui::to_string(TotalTime)) + seconds;
	///UIMan.WGListBox->addItem(printout);
	///UIMan.WGProgressBar->setText("Complete!");

	temp = "Seed: ";
	///printout = temp + (tgui::to_string(CurrentMap->Seed));
	///UIMan.WGListBox->addItem(printout);
}

void ProgramManager::SetWorldGenSettings() 
{
	/*std::string TempString;

	TempString = UIMan.WGSMapWidth->getText();
	MMan._x = std::stoi(TempString);

	TempString = UIMan.WGSMapHeight->getText();
	MMan._y = std::stoi(TempString);

	TempString = UIMan.WGSOctaves->getText();
	MMan._octaves = std::stod(TempString);

	TempString = UIMan.WGSPersistence->getText();
	MMan._persistence = std::stod(TempString);

	TempString = UIMan.WGSScale->getText();
	MMan._scale = std::stod(TempString);

	TempString = UIMan.WGSCornerSmoothScale->getText();
	MMan._CornerSmoothScale = std::stoi(TempString);

	TempString = UIMan.WGSSideSmoothScale->getText();
	MMan._SideSmoothScale = std::stoi(TempString);

	TempString = UIMan.WGSCenterSmoothScale->getText();
	MMan._CenterSmoothScale = std::stoi(TempString);

	TempString = UIMan.WGSSeedType->getText();
	MMan._SeedType = std::stoi(TempString);

	MMan._DoMapSmoothing = UIMan.WGSDoMapSmoothing->isChecked();

	MMan._DoMapSideSmoothing = UIMan.WGSDoMapSideSmoothing->isChecked();

	TempString = UIMan.WGSTempLowBound->getText();
	MMan._TempLowBound = std::stod(TempString);

	TempString = UIMan.WGSTempHighBound->getText();
	MMan._TempHighBound = std::stod(TempString);

	TempString = UIMan.WGSHeightOfEquator->getText();
	MMan._HeightOfEquator = std::stoi(TempString);

	TempString = UIMan.WGSRainfallDivisor->getText();
	MMan._RainfallDivisor = std::stoi(TempString);

	TempString = UIMan.WGSRainfallOverlapValue->getText();
	MMan._RainfallOverlapValue = std::stoi(TempString);

	TempString = UIMan.WGSRainfallMultiplier->getText();
	MMan._RainfallOverlapMultiplier = std::stod(TempString);

	TempString = UIMan.WGSBaseWindRainfall->getText();
	MMan._BaseWindRainfall = std::stoi(TempString);

	TempString = UIMan.WGSPostMountainRainfall->getText();
	MMan._PostMountainWindRainfall = std::stoi(TempString);

	TempString = UIMan.WGSPostWaterRainfall->getText();
	MMan._PostWaterWindRainfall = std::stoi(TempString);

	TempString = UIMan.WGSRainfallIncreaseDelta->getText();
	MMan._RainfallIncreaseDelta = std::stod(TempString);

	TempString = UIMan.WGSRainfallDecreaseDelta->getText();
	MMan._RainfallDecreaseDelta = std::stod(TempString);

	TempString = UIMan.WGSRainfallMultiplier->getText();
	MMan._RainfallMultiplier = std::stod(TempString);

	TempString = UIMan.WGSMountainRate1->getText();
	MMan._MountainRate1 = std::stoi(TempString);

	TempString = UIMan.WGSMountainRate2->getText();
	MMan._MountainRate2 = std::stoi(TempString);

	TempString = UIMan.WGSLandDecreaseLevel->getText();
	MMan._LandDecreaseLevel = std::stoi(TempString);

	TempString = UIMan.WGSMountainDecreaseLevel->getText();
	MMan._MountainDecreaseLevel = std::stoi(TempString);

	TempString = UIMan.WGSRainfallNoiseThreshold->getText();
	MMan._RainfallNoiseThreshold = std::stoi(TempString);

	MMan._HeightTurbulence = UIMan.WGSHeightTurbulence->isChecked();

	TempString = UIMan.WGSSeaLevel->getText();
	MMan._SeaLevel = std::stoi(TempString);

	TempString = UIMan.WGSMountainLevel->getText();
	MMan._MountainLevel = std::stoi(TempString);

	TempString = UIMan.WGSSnowLevel->getText();
	MMan._SnowLevel = std::stoi(TempString);

	TempString = UIMan.WGSMinimumWaterBodySize->getText();
	MMan._MinimumWaterBodySize = std::stoi(TempString);

	TempString = UIMan.WGSNumberOfHeightTiers->getText();
	MMan._NumberOfTiers = std::stoi(TempString);

	TempString = UIMan.WGSMinimumSeparationDistance->getText();
	MMan._MinimumSeparationDistance = std::stoi(TempString);

	TempString = UIMan.WGSMaximumRivers->getText();
	MMan._MaxRivers = std::stoi(TempString);

	TempString = UIMan.WGSMaximumVariance->getText();
	MMan._MaximumVariance = std::stoi(TempString);

	TempString = UIMan.WGSMaximumSameMoveDirection->getText();
	MMan._MaximumSameMoveDirection = std::stoi(TempString);

	MMan._SameMoveRestrictions = UIMan.WGSSameMoveRestrictions->isChecked();

	MMan._DirectionRestrictions = UIMan.WGSDirectionRestrictions->isChecked();

	TempString = UIMan.WGSMinimumTargetSize->getText();
	MMan._MinimumTargetSize = std::stoi(TempString);*/
}

void ProgramManager::UpdateWorldGenSettings() 
{/*
	//WGSProfileName->setText();
	UIMan.WGSMapWidth->setText(tgui::to_string(MMan._x));
	UIMan.WGSMapHeight->setText(tgui::to_string(MMan._y));
	UIMan.WGSOctaves->setText(tgui::to_string(MMan._octaves));
	UIMan.WGSPersistence->setText(tgui::to_string(MMan._persistence));
	UIMan.WGSScale->setText(tgui::to_string(MMan._scale));
	UIMan.WGSCornerSmoothScale->setText(tgui::to_string(MMan._CornerSmoothScale));
	UIMan.WGSSideSmoothScale->setText(tgui::to_string(MMan._SideSmoothScale));
	UIMan.WGSCenterSmoothScale->setText(tgui::to_string(MMan._CenterSmoothScale));
	UIMan.WGSSeedType->setText(tgui::to_string(MMan._SeedType));
	UIMan.WGSTempLowBound->setText(tgui::to_string(MMan._TempLowBound));
	UIMan.WGSTempHighBound->setText(tgui::to_string(MMan._TempHighBound));
	UIMan.WGSHeightOfEquator->setText(tgui::to_string(MMan._HeightOfEquator));
	UIMan.WGSRainfallDivisor->setText(tgui::to_string(MMan._RainfallDivisor));
	UIMan.WGSRainfallOverlapValue->setText(tgui::to_string(MMan._RainfallOverlapValue));
	UIMan.WGSRainfallOverlapMultiplier->setText(tgui::to_string(MMan._RainfallOverlapMultiplier));
	UIMan.WGSBaseWindRainfall->setText(tgui::to_string(MMan._BaseWindRainfall));
	UIMan.WGSPostMountainRainfall->setText(tgui::to_string(MMan._PostMountainWindRainfall));
	UIMan.WGSPostWaterRainfall->setText(tgui::to_string(MMan._PostWaterWindRainfall));
	UIMan.WGSRainfallIncreaseDelta->setText(tgui::to_string(MMan._RainfallIncreaseDelta));
	UIMan.WGSRainfallDecreaseDelta->setText(tgui::to_string(MMan._RainfallDecreaseDelta));
	UIMan.WGSRainfallMultiplier->setText(tgui::to_string(MMan._RainfallMultiplier));
	UIMan.WGSMountainRate1->setText(tgui::to_string(MMan._MountainRate1));
	UIMan.WGSMountainRate2->setText(tgui::to_string(MMan._MountainRate2));
	UIMan.WGSLandDecreaseLevel->setText(tgui::to_string(MMan._LandDecreaseLevel));
	UIMan.WGSMountainDecreaseLevel->setText(tgui::to_string(MMan._MountainDecreaseLevel));
	UIMan.WGSRainfallNoiseThreshold->setText(tgui::to_string(MMan._RainfallNoiseThreshold));
	UIMan.WGSSeaLevel->setText(tgui::to_string(MMan._SeaLevel));
	UIMan.WGSMountainLevel->setText(tgui::to_string(MMan._MountainLevel));
	UIMan.WGSSnowLevel->setText(tgui::to_string(MMan._SnowLevel));
	UIMan.WGSMinimumWaterBodySize->setText(tgui::to_string(MMan._MinimumWaterBodySize));
	UIMan.WGSNumberOfHeightTiers->setText(tgui::to_string(MMan._NumberOfTiers));
	UIMan.WGSMinimumSeparationDistance->setText(tgui::to_string(MMan._MinimumSeparationDistance));
	UIMan.WGSMaximumRivers->setText(tgui::to_string(MMan._MaxRivers));
	UIMan.WGSMaximumVariance->setText(tgui::to_string(MMan._MaximumVariance));
	UIMan.WGSMaximumSameMoveDirection->setText(tgui::to_string(MMan._MaximumSameMoveDirection));
	UIMan.WGSMinimumTargetSize->setText(tgui::to_string(MMan._MinimumTargetSize));

	if(MMan._HeightTurbulence == 1)
	{
		if(UIMan.WGSHeightTurbulence->isChecked() == 0)
		{
			UIMan.WGSHeightTurbulence->check();
		}
	}
	else if(MMan._HeightTurbulence == 0)
	{
		if(UIMan.WGSHeightTurbulence->isChecked() == 1)
		{
			UIMan.WGSHeightTurbulence->uncheck();
		}
	}

	if(MMan._DoMapSmoothing == 1)
	{
		if(UIMan.WGSDoMapSmoothing->isChecked() == 0)
		{
			UIMan.WGSDoMapSmoothing->check();
		}
	}
	else if(MMan._DoMapSmoothing == 0)
	{
		if(UIMan.WGSDoMapSmoothing->isChecked() == 1)
		{
			UIMan.WGSDoMapSmoothing->uncheck();
		}
	}

	if(MMan._DoMapSideSmoothing == 1)
	{
		if(UIMan.WGSDoMapSideSmoothing->isChecked() == 0)
		{
			UIMan.WGSDoMapSideSmoothing->check();
		}
	}
	else if(MMan._DoMapSideSmoothing == 0)
	{
		if(UIMan.WGSDoMapSideSmoothing->isChecked() == 1)
		{
			UIMan.WGSDoMapSideSmoothing->uncheck();
		}
	}

	if(MMan._DirectionRestrictions == 1)
	{
		if(UIMan.WGSDirectionRestrictions->isChecked() == 0)
		{
			UIMan.WGSDirectionRestrictions->check();
		}
	}
	else if(MMan._DirectionRestrictions == 0)
	{
		if(UIMan.WGSDirectionRestrictions->isChecked() == 1)
		{
			UIMan.WGSDirectionRestrictions->uncheck();
		}
	}

	if(MMan._SameMoveRestrictions == 1)
	{
		if(UIMan.WGSSameMoveRestrictions->isChecked() == 0)
		{
			UIMan.WGSSameMoveRestrictions->check();
		}
	}
	else if(MMan._SameMoveRestrictions == 0)
	{
		if(UIMan.WGSSameMoveRestrictions->isChecked() == 1)
		{
			UIMan.WGSSameMoveRestrictions->uncheck();
		}
	}*/
}

void ProgramManager::OpenProgramSettings()
{
	///UIMan.InProgramSettings = 1;
	//UIMan.ProgramSettingsForm->show();
	if(DisplayRiverStartPoints == 1)
	{
		//if(UIMan.SettingsCheckBox1->isChecked() == 0)
		{
			//UIMan.SettingsCheckBox1->check();
		}
	}
	else if(DisplayRiverStartPoints == 0)
	{
		//if(UIMan.SettingsCheckBox1->isChecked() == 1)
		{
			//UIMan.SettingsCheckBox1->uncheck();
		}
	}
}

void ProgramManager::CloseProgramSettings()
{
	///UIMan.InProgramSettings = 0;
	//UIMan.ProgramSettingsForm->hide();
}

bool ProgramManager::LoadProgramSettings()
{
	std::string ExePath = GetExePath();
	fs::remove(ExePath + "/Logs/Load Log.txt");
	std::ofstream LogFile(ExePath + "/Logs/Load Log.txt");

	if (fs::exists(ExePath + "/Settings/Settings.json"))
	{
		//LogFile << "Settings.json found. Loading into string buffer..." << std::endl;

		//LogFile << "Preparing to parse..." << std::endl;

		try
		{
			LogFile << "Parsing Settings.json..." << std::endl;
			std::ifstream Config(ExePath + "/Settings/Settings.json");
			Config >> MainConfig;
			Config.close();
			//MainConfig.parse(Buffer);
			//LogFile << "Done parsing Settings.json" << std::endl;
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Parse error while parsing Settings.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Exception when parsing Settings.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse Settings.json, exiting." << std::endl;
			return false;
		}
		catch (std::exception& Exception)
		{
			LogFile << "General exception when parsing Settings.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("General exception when parsing Settings.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception", MB_OK);
			LogFile << "Failed to parse Settings.json, exiting." << std::endl;
			return false;
		}
		catch (...)
		{
			LogFile << "Default exception when parsing settings.json!" << std::endl;

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception while parsing Settings.json", "Json parsing exception", MB_OK);
			LogFile << "Failed to parse Settings.json, exiting." << std::endl;
			return false;
		}
		/*catch (nlohmann::json::basic_json::invalid_iterator& Exception)
		{

		}
		catch (nlohmann::json::basic_json::type_error& Exception)
		{

		}
		catch (nlohmann::json::basic_json::out_of_range& Exception)
		{

		}
		catch (nlohmann::json::basic_json::other_error& Exception)
		{

		}*/
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		CreateDirectoryIfNull(ExePath + "/Settings/");
		LogFile << "Settings.json not found. Creating from default values." << std::endl;

		MainConfig["Window Width"] = 1920;
		MainConfig["Window Height"] = 1080;
		MainConfig["Fullscreen"] = false;
		MainConfig["Anti Aliasing Level"] = 0;
		MainConfig["Use VSync"] = true;
		MainConfig["Framerate Limit"] = 0;
		MainConfig["Automatic GL Version"] = true;
		MainConfig["GL Major"] = 3;
		MainConfig["GL Minor"] = 0;
		MainConfig["Font Location"] = "fonts/DejaVuSans.ttf";
		MainConfig["GUI Config Location"] = "widgets/MaterialBlackGold.conf";

		std::ofstream ConfigOutput(ExePath + "/Settings/Settings.json");
		ConfigOutput << std::setw(4) << MainConfig << std::endl;
		ConfigOutput.close();
	}

	WindowWidth = MainConfig["Window Width"].get<int>();
	WindowHeight = MainConfig["Window Height"].get<int>();
	Fullscreen = MainConfig["Fullscreen"].get<bool>();
	AntiAliasingLevel = MainConfig["Anti Aliasing Level"].get<int>();
	VSync = MainConfig["Use VSync"].get<bool>();
	FramerateLimit = MainConfig["Framerate Limit"].get<int>();
	AutoGL = MainConfig["Automatic GL Version"].get<bool>();
	GLMajor = MainConfig["GL Major"].get<int>();
	GLMinor = MainConfig["GL Minor"].get<int>();
	FontLocation = MainConfig["Font Location"].get<std::string>();
	GuiConfigLocation = MainConfig["GUI Config Location"].get<std::string>();

	///UIMan.FontLocation = FontLocation;
	///UIMan.ConfigLocation = GuiConfigLocation;

	LogFile.close();
	return true;
}

void ProgramManager::SaveProgramSettings() //Todo: Add exception catching.
{
	MainConfig["Window Width"] = WindowWidth;
	MainConfig["Window Height"] = WindowHeight;
	MainConfig["Full screen"] = Fullscreen;
	MainConfig["Anti Aliasing Level"] = AntiAliasingLevel;
	MainConfig["Use VSync"] = VSync;
	MainConfig["Framerate Limit"] = FramerateLimit;
	MainConfig["GL Major"] = GLMajor;
	MainConfig["GL Minor"] = GLMinor;
	//MainConfig["Display River Start Points"] = DisplayRiverStartPoints;
	//MainConfig["Display As Tiles"] = DisplayAsTiles;
	//MainConfig["UI Scale Factor"] = UIScaleFactor;

	std::ofstream ConfigOutput(GetExePath() + "/Settings/Settings.json");
	ConfigOutput << std::setw(4) << MainConfig << std::endl;
	ConfigOutput.close();
}

bool ProgramManager::FileExists(std::string FileName)
{
	std::ifstream fin(FileName);

	if(fin.fail() == 0)
	{
		fin.close();
		return 1;
	}
	if(fin.fail() == 1)
	{
		fin.close();
		return 0;
	}
}

bool ProgramManager::LoadWorldGenSettings()
{
	std::string ExePath = GetExePath();
	fs::remove(ExePath + "/Logs/Load Log.txt");
	std::ofstream LogFile(ExePath + "/Logs/Load Log.txt");

	if (fs::exists(ExePath + "/Settings/World Gen Settings.json"))
	{
		//LogFile << "World Gen Settings.json found. Loading into string buffer..." << std::endl;

		//LogFile << "Preparing to parse..." << std::endl;

		try
		{
			LogFile << "Parsing World Gen Settings.json..." << std::endl;
			std::ifstream Config(ExePath + "/Settings/World Gen Settings.json");
			Config >> MainConfig;
			Config.close();
			//MainConfig.parse(Buffer);
			//LogFile << "Done parsing World Gen Settings.json" << std::endl;
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Parse error while parsing World Gen Settings.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Exception when parsing World Gen Settings.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse World Gen Settings.json, exiting." << std::endl;
			return false;
		}
		catch (std::exception& Exception)
		{
			LogFile << "General exception when parsing World Gen Settings.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("General exception when parsing World Gen Settings.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception", MB_OK);
			LogFile << "Failed to parse World Gen Settings.json, exiting." << std::endl;
			return false;
		}
		catch (...)
		{
			LogFile << "Default exception when parsing World Gen Settings.json!" << std::endl;

			//MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception while parsing Settings.json", "Json parsing exception", MB_OK);
			LogFile << "Failed to parse World Gen Settings.json, exiting." << std::endl;
			return false;
		}
		/*catch (nlohmann::json::basic_json::invalid_iterator& Exception)
		{

		}
		catch (nlohmann::json::basic_json::type_error& Exception)
		{

		}
		catch (nlohmann::json::basic_json::out_of_range& Exception)
		{

		}
		catch (nlohmann::json::basic_json::other_error& Exception)
		{

		}*/
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		CreateDirectoryIfNull(ExePath + "/Settings/");
		LogFile << "World Gen Settings.json not found. Creating from default values." << std::endl;

		MainConfig["Profile Name"] = "Default World Gen";
		MainConfig["Map Height"] = 400;
		MainConfig["Map Width"] = 256;
		MainConfig["Octaves"] = 30.0f;
		MainConfig["Persistence"] = 0.65f;
		MainConfig["Scale"] = 0.0065f;
		MainConfig["Corner Smooth Scale"] = 16;
		MainConfig["Side Smooth Scale"] = 8;
		MainConfig["Center Smooth Scale"] = 1;
		MainConfig["Seed"] = 0;
		MainConfig["Do Map Smoothing"] = false;
		MainConfig["Do Map Side Smoothing"] = false;
		MainConfig["Temp Low Bound"] = 273.3f;
		MainConfig["Temp High Bound"] = 318.15f;
		MainConfig["Height of Equator"] = 2;
		MainConfig["Rainfall Divisor"] = 4;
		MainConfig["Rainfall Overlap Value"] = 70;
		MainConfig["Rainfall Multiplier"] = 4;
		MainConfig["Base Wind Rainfall"] = 135;
		MainConfig["Post Mountain Wind Rainfall"] = 35;
		MainConfig["Post Water Wind Rainfall"] = 180;
		MainConfig["Rainfall Increase Delta"] = 2.5f;
		MainConfig["Rainfall Decrease Delta"] = 1.5f;
		MainConfig["Rainfall Multiplier"] = 6.0f;
		MainConfig["Mountain Rate 1"] = 4;
		MainConfig["Mountain Rate 2"] = 4;
		MainConfig["Land Decrease Level"] = 28;
		MainConfig["Mountain Decrease Level"] = 10;
		MainConfig["Rainfall Noise Threshold"] = 170.0f;
		MainConfig["Height Turbulence"] = true;
		MainConfig["Sea Level"] = 130;
		MainConfig["Mountain Level"] = 170;
		MainConfig["Snow Level"] = 200;
		MainConfig["Minimum Water Body Size"] = 30;
		MainConfig["Number of Height Tiers"] = 8;
		MainConfig["Minimum Separation Distance"] = 5;
		MainConfig["Maximum Rivers"] = 120;
		MainConfig["Maximum Variance"] = 10;
		MainConfig["Maximum Same Move Direction"] = 7;
		MainConfig["Same Move Restrictions"] = false;
		MainConfig["Direction Restrictions"] = false;
		MainConfig["Minimum Target Size"] = 60;
		
		std::ofstream ConfigOutput(ExePath + "/Settings/World Gen Settings.json");
		ConfigOutput << std::setw(4) << MainConfig << std::endl;
		ConfigOutput.close();
	}

	MMan.ProfileName = MainConfig["Profile Name"].get<std::string>();
	MMan._x = MainConfig["Map Width"].get<int>();
	MMan._y = MainConfig["Map Height"].get<int>();
	MMan._octaves = MainConfig["Octaves"].get<float>();
	MMan._persistence = MainConfig["Persistence"].get<float>();
	MMan._scale = MainConfig["Scale"].get<float>();
	MMan._CornerSmoothScale = MainConfig["Corner Smooth Scale"].get<int>();
	MMan._SideSmoothScale = MainConfig["Side Smooth Scale"].get<int>();
	MMan._CenterSmoothScale = MainConfig["Center Smooth Scale"].get<int>();
	MMan._SeedType = MainConfig["Seed"].get<int>();
	MMan._DoMapSmoothing = MainConfig["Do Map Smoothing"].get<bool>();
	MMan._DoMapSideSmoothing = MainConfig["Do Map Side Smoothing"].get<bool>();
	MMan._TempLowBound = MainConfig["Temp Low Bound"].get<float>();
	MMan._TempHighBound = MainConfig["Temp High Bound"].get<float>();
	MMan._HeightOfEquator = MainConfig["Height of Equator"].get<int>();
	MMan._RainfallDivisor = MainConfig["Rainfall Divisor"].get<float>();
	MMan._RainfallOverlapValue = MainConfig["Rainfall Overlap Value"].get<float>();
	MMan._RainfallMultiplier = MainConfig["Rainfall Multiplier"].get<float>();
	MMan._BaseWindRainfall = MainConfig["Base Wind Rainfall"].get<float>();
	MMan._PostMountainWindRainfall = MainConfig["Post Mountain Wind Rainfall"].get<float>();
	MMan._PostWaterWindRainfall = MainConfig["Post Water Wind Rainfall"].get<float>();
	MMan._RainfallIncreaseDelta = MainConfig["Rainfall Increase Delta"].get<float>();
	MMan._RainfallDecreaseDelta = MainConfig["Rainfall Decrease Delta"].get<float>();
	MMan._RainfallMultiplier = MainConfig["Rainfall Multiplier"].get<float>();
	MMan._MountainRate1 = MainConfig["Mountain Rate 1"].get<float>();
	MMan._MountainRate2 = MainConfig["Mountain Rate 2"].get<float>();
	MMan._LandDecreaseLevel = MainConfig["Land Decrease Level"].get<float>();
	MMan._MountainDecreaseLevel = MainConfig["Mountain Decrease Level"].get<float>();
	MMan._RainfallNoiseThreshold = MainConfig["Rainfall Noise Threshold"].get<float>();
	MMan._HeightTurbulence = MainConfig["Height Turbulence"].get<bool>();
	MMan._SeaLevel = MainConfig["Sea Level"].get<int>();
	MMan._MountainLevel = MainConfig["Mountain Level"].get<int>();
	MMan._SnowLevel = MainConfig["Snow Level"].get<int>();
	MMan._MinimumWaterBodySize = MainConfig["Minimum Water Body Size"].get<int>();
	MMan._NumberOfTiers = MainConfig["Number of Height Tiers"].get<int>();
	MMan._MinimumSeparationDistance = MainConfig["Minimum Separation Distance"].get<int>();
	MMan._MaxRivers = MainConfig["Maximum Rivers"].get<int>();
	MMan._MaximumVariance = MainConfig["Maximum Variance"].get<int>();
	MMan._MaximumSameMoveDirection = MainConfig["Maximum Same Move Direction"].get<int>();
	MMan._SameMoveRestrictions = MainConfig["Same Move Restrictions"].get<bool>();
	MMan._DirectionRestrictions = MainConfig["Direction Restrictions"].get<bool>();
	MMan._MinimumTargetSize = MainConfig["Minimum Target Size"].get<int>();

	LogFile.close();
	return true;
}

void ProgramManager::SaveWorldGenSettings() //Todo: Add exception handling
{
	CreateDirectoryIfNull(GetExePath() + "/Settings/");

	MainConfig["Profile Name"] = MMan.ProfileName;
	MainConfig["Map Height"] = MMan._x;
	MainConfig["Map Width"] = MMan._y;
	MainConfig["Octaves"] = MMan._octaves;
	MainConfig["Persistence"] = MMan._persistence;
	MainConfig["Scale"] = MMan._scale;
	MainConfig["Corner Smooth Scale"] = MMan._CornerSmoothScale;
	MainConfig["Side Smooth Scale"] = MMan._SideSmoothScale;
	MainConfig["Center Smooth Scale"] = MMan._CenterSmoothScale;
	MainConfig["Seed"] = MMan._Seed;
	MainConfig["Do Map Smoothing"] = MMan._DoMapSmoothing;
	MainConfig["Do Map Side Smoothing"] = MMan._DoMapSideSmoothing;
	MainConfig["Temp Low Bound"] = MMan._TempLowBound;
	MainConfig["Temp High Bound"] = MMan._TempHighBound;
	MainConfig["Height of Equator"] = MMan._HeightOfEquator;
	MainConfig["Rainfall Divisor"] = MMan._RainfallDivisor;
	MainConfig["Rainfall Overlap Value"] = MMan._RainfallOverlapValue;
	MainConfig["Rainfall Multiplier"] = MMan._RainfallMultiplier;
	MainConfig["Base Wind Rainfall"] = MMan._BaseWindRainfall;
	MainConfig["Post Mountain Wind Rainfall"] = MMan._PostMountainWindRainfall;
	MainConfig["Post Water Rainfall"] = MMan._PostWaterWindRainfall;
	MainConfig["Rainfall Increase Delta"] = MMan._RainfallIncreaseDelta;
	MainConfig["Rainfall Decrease Delta"] = MMan._RainfallDecreaseDelta;
	MainConfig["Rainfall Multiplier"] = MMan._RainfallMultiplier;
	MainConfig["Mountain Rate 1"] = MMan._MountainRate1;
	MainConfig["Mountain Rate 2"] = MMan._MountainRate2;
	MainConfig["Land Decrease Level"] = MMan._LandDecreaseLevel;
	MainConfig["Mountain Decrease Level"] = MMan._MountainDecreaseLevel;
	MainConfig["Rainfall Noise Threshold"] = MMan._RainfallNoiseThreshold;
	MainConfig["Height Turbulence"] = MMan._HeightTurbulence;
	MainConfig["Sea Level"] = MMan._SeaLevel;
	MainConfig["Mountain Level"] = MMan._MountainLevel;
	MainConfig["Snow Level"] = MMan._SnowLevel;
	MainConfig["Minimum Water Body Size"] = MMan._MinimumWaterBodySize;
	MainConfig["Number of Height Tiers"] = MMan._NumberOfTiers;
	MainConfig["Minimum Separation Distance"] = MMan._MinimumSeparationDistance;
	MainConfig["Maximum Rivers"] = MMan._MaxRivers;
	MainConfig["Maximum Variance"] = MMan._MaximumVariance;
	MainConfig["Maximum Same Move Direction"] = MMan._MaximumSameMoveDirection;
	MainConfig["Same Move Restrictions"] = MMan._SameMoveRestrictions;
	MainConfig["Direction Restrictions"] = MMan._DirectionRestrictions;
	MainConfig["Minimum Target Size"] = MMan._MinimumTargetSize;

	std::ofstream ConfigOutput(GetExePath() + "/Settings/World Gen Settings.json");
	ConfigOutput << std::setw(4) << MainConfig << std::endl;
	ConfigOutput.close();
}
