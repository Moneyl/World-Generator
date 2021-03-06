//#include "Files.h"
#include "WorldTile.h"

static float NoiseFrequency = 0.005f;

namespace MapSystem
{

class NatureRegion
{
public:
    NatureRegion() {};
    ~NatureRegion() {};

    bool Contains(int Position);
    void AddCoordinate(int  Position);

    int CenterX;
    int CenterY;
    int Type;

    sf::Color RegionColor;
    bool ColorSet = 0;

    std::vector <int> ContainedCoordinates;
};

class GameMap
{

public:

    GameMap(int _x, int _y) : x(_x), y(_y) // set the dimensions
    {
        data = new WorldTile[x * y];
        MapSize = (x * y) - 1;
        SetWorldTileCoordinates();
    };

    GameMap() {};

    ~GameMap()
    {
        delete [] data; 
    };

    WorldTile &operator[](int arraypos)
    {
        return data[arraypos];
    };

    void CreateWorldMap(int _x, int _y)
    {
        x = _x;
        y = _y;

        data = new WorldTile[x * y];
        MapSize = (x * y) - 1;
        SetWorldTileCoordinates();
    }

    void CreateWorldMap()
    {
        data = new WorldTile[x * y];
        MapSize = (x * y) - 1;
        SetWorldTileCoordinates();
    }

    void Reset()
    {
        delete [] data;

        while(NatureRegionsContainer.empty() == 0)
        {
            NatureRegionsContainer.pop_back();
        }
    }

    void GenerateHeightMap();
    void Turbulence();
    void CalculateMapRainfall(bool DebugMessages);
    void SetTileBiomes();
    void FlattenIsolatedWater();

    void CalculateRainShadow(bool DebugMessages);
    void ApplyNoiseToRainfall();

    int GetRiverDirection(int Position);
    void SetRiverBaseColor(int Position);
    void SetMountainBaseColor(int Position);

    int ConvertToAbsolute(int xpos, int ypos);
    //CartesianCoordinate ConvertToCoordinate(int AbsolutePosition);
    bool RegionContainsCoordinate(int AbsolutePosition);
    void SetWorldTileCoordinates();
    void SetSlopeValues();

    int GetDistance(int PositionOne, int PositionTwo);

    int sizeX()
    {
        return x;
    }

    int sizeY()
    {
        return y;
    }

    void SetGenerationVariables(float aOctaves, float aPersistence, float aScale, float aAmplitude)
    {
        octaves = aOctaves;
        persistence = aPersistence;
        scale = aScale;
        amplitude = aAmplitude;
    }

    void SetSmoothScales(int aCorner, int aSide, int aCenter)
    {
        CornerSmoothScale = aCorner;
        SideSmoothScale = aSide;
        CenterSmoothScale = aCenter;
    }

    void SetSeedType(int aSeedType)
    {
        SeedType = aSeedType;
    }

    void InterpolateX();
    void InterpolateY();
    void InterpolateBoth();

    void SmoothNoise(bool DebugMessages);
    void SmoothNoiseOutside(bool DebugMessages);

    float ConvertTempToCelsius(float aTemp);
    float ConvertTempToWorld(float aTemp);

    int IsCorner(int cx, int cy);
    int IsSide(int sx, int sy);
    bool IsCenter(int cex, int cey);

    bool IsDeepOcean(int Position);
    bool IsDeepMountain(int Position);
    bool IsIsolatedWater(int Position);
    bool IsBiomeBorder(int Position);

    void CalculateMapRegions(bool DebugMessages);

    void ApplyNoiseToTemperature();
    void GenerateTemperatureMap();//Alternate Method;

    void SetWindAngles();
    void ApplyNoiseToWindAngles();
    int GetChannelHeight();

    void IncrementModifiers();

    bool InBounds(int XPos, int YPos);
    bool InBounds(int Position);
    int SetBaseWindRainfall(int Position);

    bool InvalidAngle(int Angle);
    void SmoothRainfall();

    int MinimumChannelHeight = 10;
    int MaximumChannelHeight = 20;

    int MaximumAngle = 359;
    int MaximumNoiseAngle = 90;

    float ModifierOne = .01f;
    float ModifierTwo = .0001f;

    float ModOneAdd = .01f;
    float ModTwoAdd = .0003f;

    float ModOneMax = 3.0f;
    float ModTwoMax = .01f;

    std::vector <int> ChannelLocations;

    std::string BiomeToString(int TileID);

    WorldTile *data; // the data
    int x, y; // the dimensions
    int MapSize;

    float octaves;
    float persistence;
    float scale;
    float amplitude;

    int CornerSmoothScale;
    int SideSmoothScale;
    int CenterSmoothScale;

    int SeedType;
    float SeedModifier = .001f;

    float TempLowBound; //Both in Celsius
    float TempHighBound;

    float TempRange;
    float TempChangeDelta;

    int HeightOfEquator; // Preferably an even number to make the equator look nice.

    float RainfallDivisor;
    float RainfallOverlapValue;
    float RainfallOverlapMultiplier;

    float BaseWindRainfall;
    float PostMountainWindRainfall;
    float PostWaterWindRainfall;
    float RainfallIncreaseDelta;
    float RainfallDecreaseDelta;
    float RainfallMultiplier;

    float MountainRate1;
    float MountainRate2;

    float LandDecreaseLevel;
    float MountainDecreaseLevel;

    float RainfallNoiseThreshold;
    bool HeightTurbulence;

    int SeaLevel;
    int MountainLevel;
    int SnowLevel;

    float TemperatureMultiplier = 0.6f;
    float TemperatureDivisor = 30.0f;

    std::vector <NatureRegion> NatureRegionsContainer;

    int Seed;
};

class WeatherSystem
{
public:
    WeatherSystem() {};
    ~WeatherSystem() {};

    bool Contains(int XPos, int YPos);
    bool Contains(int Position);

    int CenterTile;
    int MovementAngle;
    int MovementSpeed;
    int Radius;
    int Moisture;
};

class WeatherSystemManager
{
public:
    WeatherSystemManager() {};
    ~WeatherSystemManager() {};

    void Reset();
    void RunWeather();
    void Step(int StepsToTake);
    void SetWindAngles();
    void ApplyNoiseToWindAngles();
    int GetChannelHeight();

    int AddSystem();
    void RemoveSystem(int SystemID);

    void IncrementModifiers();

    int GetStartTile();
    int GetStartMoveSpeed();
    int GetStartRadius();
    int GetStartMoisture();
    bool UsedStartPosition(int Position);
    int GetResultantAngle(int AngleOne, int AngleTwo);

    float PropagateRainfall(int SystemID);

    MapSystem::GameMap* CurrentMap;

    std::vector <MapSystem::WeatherSystem> ContainedSystems;
    std::vector <int> StartPositions;

    int CurrentID = 0;
    int IDCount = 0;

    int StepLimit = 1000;//300;
    int TotalSystems;

    float RainfallDivisor = 1.0f; //Modifies how quickly moisture within a system transfers to the ground below. Used so systems don't immediately turn anything they pass over into a rainforest.
    float CloudgainDivisor = 4.0f; //Modifies how quickly a system can gain moisture from water or other moisture source.

    int MinimumChannelHeight = 10;
    int MaximumChannelHeight = 20;

    int MaximumAngle = 360;
    int MaximumNoiseAngle = 90;

    bool UseVaryingRadius = true;
    int MinimumRadius = 4;
    int MaximumRadius = 15;
    int ConstantRadius = 15;

    bool UseVaryingStartSpeed = true;
    int MinimumStartSpeed = 1;
    int MaximumStartSpeed = 3;
    int ConstantStartSpeed = 4;

    bool UseVaryingStartMoisture = true;
    int MinimumStartMoisture = 50;
    int MaximumStartMoisture = 200;
    int ConstantStartMoisture = 255;

    float ModifierOne = .01f;
    float ModifierTwo = .0001f;

    float ModOneAdd = .01f;
    float ModTwoAdd = .0003f;

    float ModOneMax = 20.0f;
    float ModTwoMax = .001f;
};

class WaterRegion
{
public:
    WaterRegion() {};
    ~WaterRegion() {};

    bool Contains(int XPos, int YPos);
    bool Contains(int Position);

    void SetCurrentMap(MapSystem::GameMap& GMap)
    {
        CurrentMap = &GMap;
    }

    void AddCoordinate(int Position)
    {
        ContainedCoordinates.push_back(Position);
    }

    void CalculateMidpoints();

    std::vector <int> ContainedCoordinates;

    int FurthestLeftPosition = -1;
    int FurthestRightPosition = -1;
    int FurthestUpPosition = -1;
    int FurthestDownPosition = -1;

    int LeftRightMidpointPosition;
    int UpDownMidpointPosition;

    int AbsoluteMidpointPosition;

    sf::Color RegionColor;
    bool ColorSet = false;

    MapSystem::GameMap* CurrentMap;
};

class WaterRegionManager
{
public:
    WaterRegionManager() {};
    ~WaterRegionManager() {};

    void CalculateWaterRegions(bool DebugMessages);
    void SetCurrentMap(MapSystem::GameMap& GMap)
    {
        CurrentMap = &GMap;
    }
    void FlattenSmallWaterBodies();
    void ClearWaterRegions();
    void Reset();

    MapSystem::GameMap* CurrentMap;
    int MinimumWaterBodySize;

    std::vector <MapSystem::WaterRegion> ContainedRegions;
};

class HeightRegionInfo
{
public:

    HeightRegionInfo() {};
    ~HeightRegionInfo() {};

    int TierNumber;
    int MinValue;
    int MaxValue;
    int TierSize;

    sf::Color RegionColor;
    bool ColorSet = false;
};

class HeightRegion
{
public:

    HeightRegion() {};
    ~HeightRegion() {};

    void SetCurrentMap(MapSystem::GameMap* GMap)
    {
        CurrentMap = GMap;
    }

    void AddCoordinate(int Position)
    {
        RegionCoordinateContainer.push_back(Position);
    }

    bool Contains(int XVal, int YVal); //Checks if tier contains the coordinate.
    bool Contains(int Position); //Overloaded version of above.

    std::vector <int> RegionCoordinateContainer;
    int HeightRegionNumber;
    int TierNumber;
    int TierMin;
    int TierMax;

    MapSystem::GameMap* CurrentMap;
};

class HeightRegionManager
{
public:

    HeightRegionManager() {};
    ~HeightRegionManager() {};

    void CreateHeightBounds(int NumOfTiers);
    void CalculateHeightRegions(bool DebugMessages);

    void SetCurrentMap(MapSystem::GameMap& GMap)
    {
        CurrentMap = &GMap;
    }

    bool WithinTierBounds(int CurrentTier, int Value); //Checks if value is within the bounds of the given tier.
    bool Contained(int Position); //Checks if any tiers contain the value.
    void Reset();

    std::vector <MapSystem::HeightRegionInfo> HeightTierContainer;
    std::vector <MapSystem::HeightRegion> HeightRegionContainer;

    int NumberOfTiers;

    MapSystem::GameMap* CurrentMap;

};

class River
{
public:

    River() {};
    ~River() {};

    bool Contains(int XVal, int YVal);
    bool Contains(int Position);

    void SetCurrentMap(MapSystem::GameMap& GMap)
    {
        CurrentMap = &GMap;
    }

    int StartPos;
    int EndPos;

    int Length;
    int Width;

    bool IsParent;
    bool IsChild;
    bool HitOcean;
    bool HitDeadEnd;
    int LastMoveDirection;

    bool NoLeft = false;
    bool NoRight = false;
    bool NoUp = false;
    bool NoDown = false;

    void AddAdjacentTiles(int Position);
    bool IsAdjacentToSelf(int Position);

    MapSystem::GameMap* CurrentMap;

    std::vector <int> AdjacentTiles;
    std::vector <int> ContainedCoordinates;
};

class RiverManager
{
public:

    RiverManager() {};
    ~RiverManager() {};

    void SetCurrentMap(MapSystem::GameMap& GMap)
    {
        CurrentMap = &GMap;
    }

    int PickStartPosition();
    bool ContainedStartPoint(int Position);
    int ClosestStartPoint(int Position);
    int NextPosition(int Position, bool DebugMessages);
    int RandomDirection(int Position, int RestrictedDirection); //1 = Left, 2 = Right, 3 = Up, 4 = Down.
    int TestPositionFinder(int Position);
    bool SurroundedByObstacles(int Position);
    bool SurroundedByMountains(int Position);
    int ClosestWaterPosition(int Position);
    bool IsAdjacentToWater(int Position);
    void GenerateRivers(bool DebugMessages);
    void Reset();

    int NumberOfRivers;
    int CurrentRiver;

    int MinLength;
    int MaxLength;

    int MinWidth;
    int MaxWidth;

    int MaxRivers;

    int MinimumSeparationDistance;
    int MinimumDistanceFromWater;

    int LastMoveDirection;
    int MaximumVariance;
    int MaximumSameMoveDirection;

    bool SameMoveRestrictions = false;
    bool DirectionRestrictions = true;

    float CurrentCount = 0.01f;
    float Modifier = 0.01f;

    int MinimumTargetSize;

    MapSystem::GameMap* CurrentMap;
    MapSystem::WaterRegionManager* CurrentWRM;

    std::vector <MapSystem::River> ContainedRivers;
    std::vector <int> RiverStartPoints;
};

class MapManager
{
public:
    MapManager() { SetAsDefault(); };
    ~MapManager() {};

    GameMap MainMap;
    WeatherSystemManager MainWSM;
    WaterRegionManager MainWRM;
    HeightRegionManager MainHRM;
    RiverManager MainRM;

    void SetParameters();
    void SetAsDefault();
    void Initialize();
    void Reset();

    //MAP GEN PARAMETERS - Start as default values.
    //Main Map Parameters:

    std::string ProfileName = "Default World Gen";

    int _x = 400;
    int _y = 256;

    float _octaves = 30.0f;
    float _persistence = 0.65f;
    float _scale = 0.0065f;
    float _amplitude = 1.0f;

    int _CornerSmoothScale = 16;
    int _SideSmoothScale = 8;
    int _CenterSmoothScale = 1;
    int _SeedType = 0;

    bool _DoMapSmoothing = false;
    bool _DoMapSideSmoothing = false;

    float _TempLowBound = 273.3f; //Both in Kelvin
    float _TempHighBound = 318.15f;

    float _TempRange;
    float _TempChangeDelta;

    int _HeightOfEquator = 2; // Preferably an even number to make the equator look nice.

    float _RainfallDivisor = 4.0f;
    float _RainfallOverlapValue = 70.0f;
    float _RainfallOverlapMultiplier = 4.0f;

    float _BaseWindRainfall = 135.0f;
    float _PostMountainWindRainfall = 35.0f;
    float _PostWaterWindRainfall = 180.0f;

    float _RainfallIncreaseDelta = 2.5f;
    float _RainfallDecreaseDelta = 1.5f;
    float _RainfallMultiplier = 6.0f;

    float _MountainRate1 = 4.0f;
    float _MountainRate2 = 4.0f;

    float _LandDecreaseLevel = 28.0f;
    float _MountainDecreaseLevel = 10.0f;

	float _RainfallNoiseThreshold = 170.0f;
    bool _HeightTurbulence = true;

    int _SeaLevel = 130;
    int _MountainLevel = 190;
    int _SnowLevel = 212;

    int _Seed;

    //Water Regions:

    int _MinimumWaterBodySize = 30;

    //Height Regions:

    int _NumberOfTiers = 8;

    //Rivers:

    int _NumberOfRivers = 120;
    int _CurrentRiver;

    int _MinLength;
    int _MaxLength;

    int _MinWidth;
    int _MaxWidth;

    int _MaxRivers = 120;

    int _MinimumSeparationDistance = 5;
    int _MinimumDistanceFromWater = 6;

    int _LastMoveDirection;
    int _MaximumVariance = 10;
    int _MaximumSameMoveDirection = 7;

    bool _SameMoveRestrictions = false;
    bool _DirectionRestrictions = false;

    float _CurrentCount = 0.01f;
    float _Modifier = 0.01f;

    int _MinimumTargetSize = 60;

    int _WeatherSystemsToRun = 150;
};
}
