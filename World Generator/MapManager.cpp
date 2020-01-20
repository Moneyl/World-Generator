#include "GameMap.h"
#include "Files.h"

//Todo: Make this code for managing settings less of a maintenance hell
void MapSystem::MapManager::SetAsDefault()
{
    ProfileName = "Default World Gen";

    _x = 400;
    _y = 256;

    _octaves = 7;
    _persistence = 2.38f;
    _scale = 0.55f;
    _amplitude = 1.0f;

    _CornerSmoothScale = 16;
    _SideSmoothScale = 8;
    _CenterSmoothScale = 1;
    _SeedType = 0;

    _DoMapSmoothing = false;
    _DoMapSideSmoothing = false;

    _TempLowBound = 273.3f;
    _TempHighBound = 318.15f;

    _TempRange = 0.0f;
    _TempChangeDelta = 0.0f;

    _HeightOfEquator = 2;

    _RainfallDivisor = 4.0f;
    _RainfallOverlapValue = 70.0f;
    _RainfallOverlapMultiplier = 4.0f;

    _BaseWindRainfall = 135.0f;
    _PostMountainWindRainfall = 5.0f;
    _PostWaterWindRainfall = 180.0f;

    _RainfallIncreaseDelta = 2.5f;
    _RainfallDecreaseDelta = 1.5f;
    _RainfallMultiplier = 6.0f;

    _MountainRate1 = 4.0f;
    _MountainRate2 = 4.0f;

    _LandDecreaseLevel = 28.0f;
    _MountainDecreaseLevel = 10.0f;

    _RainfallNoiseThreshold = 170.0f;
    _HeightTurbulence = true;

    _SeaLevel = 130;
    _MountainLevel = 190;
    _SnowLevel = 212;

    _Seed = 0;

    _MinimumWaterBodySize = 30;

    _NumberOfTiers = 8;

    _NumberOfRivers = 120;
    _CurrentRiver = 0;

    _MinLength = 0;
    _MaxLength = 0;

    _MinWidth = 0;
    _MaxWidth = 0;

    _MaxRivers = 120;

    _MinimumSeparationDistance = 5;
    _MinimumDistanceFromWater = 6;

    _LastMoveDirection;
    _MaximumVariance = 10;
    _MaximumSameMoveDirection = 7;

    _SameMoveRestrictions = 0;
    _DirectionRestrictions = 1;

    _CurrentCount = 0.01f;
    _Modifier = 0.01f;

    _MinimumTargetSize = 60;

    _WeatherSystemsToRun = 150;
}

void MapSystem::MapManager::SetParameters()
{
    //Todo: Rework this when settings files are redone. 
    //MainMap.MapWidth = _MapWidth;
    //MainMap.MapHeight = _MapHeight;

    MainMap.x = _x;
    MainMap.y = _y;

    MainMap.octaves = _octaves;
    MainMap.persistence = _persistence;
    MainMap.scale = _scale;
    MainMap.amplitude = _amplitude;

    MainMap.CornerSmoothScale = _CornerSmoothScale;
    MainMap.SideSmoothScale = _SideSmoothScale;
    MainMap.CenterSmoothScale = _CenterSmoothScale;
    MainMap.SeedType = _SeedType;

    //MainMap.DoMapSmoothing = _DoMapSmoothing;
    //MainMap.DoMapSideSmoothing = _DoMapSideSmoothing;

    MainMap.TempLowBound = _TempLowBound;
    MainMap.TempHighBound = _TempHighBound;

    MainMap.TempRange = _TempRange;
    MainMap.TempChangeDelta = _TempChangeDelta;

    MainMap.HeightOfEquator = _HeightOfEquator;

    MainMap.RainfallDivisor = _RainfallDivisor;
    MainMap.RainfallOverlapValue = _RainfallOverlapValue;
    MainMap.RainfallOverlapMultiplier = _RainfallOverlapMultiplier;

    MainMap.BaseWindRainfall = _BaseWindRainfall;
    MainMap.PostMountainWindRainfall = _PostMountainWindRainfall;
    MainMap.PostWaterWindRainfall = _PostWaterWindRainfall;

    MainMap.RainfallIncreaseDelta = _RainfallIncreaseDelta;
    MainMap.RainfallDecreaseDelta = _RainfallDecreaseDelta;
    MainMap.RainfallMultiplier = _RainfallMultiplier;

    MainMap.MountainRate1 = _MountainRate1;
    MainMap.MountainRate2 = _MountainRate2;

    MainMap.LandDecreaseLevel = _LandDecreaseLevel;
    MainMap.MountainDecreaseLevel = _MountainDecreaseLevel;

    MainMap.RainfallNoiseThreshold = _RainfallNoiseThreshold;
    MainMap.HeightTurbulence = _HeightTurbulence;

    MainMap.SeaLevel = _SeaLevel;
    MainMap.MountainLevel = _MountainLevel;
    MainMap.SnowLevel = _SnowLevel;

    MainWRM.MinimumWaterBodySize = _MinimumWaterBodySize;

    //MainHRM.NumberOfTiers = _NumberOfTiers; DOES NOTHING UNTIL COLORING SCHEME FOR MORE THAN 8 TIERS IS FIGURED.

    MainRM.NumberOfRivers = _NumberOfRivers;

    //MainRM.MinLength;
    //MainRM.MaxLength;

    //MainRM.MinWidth;
    //MainRM.MaxWidth;

    MainRM.MaxRivers = _MaxRivers;

    MainRM.MinimumSeparationDistance = _MinimumSeparationDistance;
    MainRM.MinimumDistanceFromWater = _MinimumDistanceFromWater;

    MainRM.LastMoveDirection = _LastMoveDirection;
    MainRM.MaximumVariance = _MaximumVariance;
    MainRM.MaximumSameMoveDirection = _MaximumSameMoveDirection;

    MainRM.SameMoveRestrictions = _SameMoveRestrictions;
    MainRM.DirectionRestrictions = _DirectionRestrictions;

    MainRM.MinimumTargetSize = _MinimumTargetSize;

    MainWSM.TotalSystems = _WeatherSystemsToRun;
}

void MapSystem::MapManager::Initialize()
{
    SetParameters();
    MainMap.CreateWorldMap();

    MainWSM.CurrentMap = &MainMap;
    MainWRM.CurrentMap = &MainMap;
    MainHRM.CurrentMap = &MainMap;
    MainRM.CurrentMap = &MainMap;
    MainRM.CurrentWRM = &MainWRM;

    MainHRM.CreateHeightBounds(8); //Edit later.
}

void MapSystem::MapManager::Reset()
{
    MainMap.Reset();
    MainWSM.Reset();
    MainHRM.Reset();
    MainWRM.Reset();
    MainRM.Reset();

    //std::cout << "\n Tile Count After Reset: " << MainMap.data;
    std::cout << "\n\nRegion Count After Reset: " << MainMap.NatureRegionsContainer.size();
    std::cout << "\nHeight Region Count After Reset: " << MainHRM.HeightRegionContainer.size();
    std::cout << "\nWater Region Count After Reset: " << MainWRM.ContainedRegions.size();
    std::cout << "\nRiver Count After Reset: " << MainRM.ContainedRivers.size() << "\n";
}
