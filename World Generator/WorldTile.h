#include "Globals.h"

class WorldTile
{
public:
    WorldTile() : x(0), y(0), z(0)
    {
        rainfall = 0;
    }

    ~WorldTile();

    int x;
    int y;
    int z;

    int WindowX;
    int WindowY;

    int WindAngle;

    float rainfall = 0;
    float temperature;
    int Biome = 0;
    int region;

    int Slope = 0;

    int MapWidth;
    int MapHeight;

    bool InBiomeRegion;
    bool InHeightRegion;

    int HeightTier;

    bool IsRiver;
    bool IsRiverStartPoint;
    int RiverID;

    bool InWaterRegion;

    bool FlattenedWater;
    bool Blended = 0;

    bool HasForeground = 1;
    bool SeparateForeground;
    sf::Color BaseColor;//Background
    sf::Color ForeColor;//Foreground

    sf::Sprite TileSprite;

    int TileID;
    int TileID2; //For separate foreground if it exists.

    int ConvertToAbsolute(int xpos, int ypos)
    {
        return ((ypos * MapWidth) + xpos);
    }

    int Left();
    int Right();
    int Above();
    int Below();
    int UpperLeft();
    int UpperRight();
    int LowerLeft();
    int LowerRight();
    bool IsBorderTile();
    int IsCorner();
    int IsSide();

protected:

private:

};
