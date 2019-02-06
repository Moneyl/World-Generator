#include "Globals.h"

class Tileset
{
public:
    Tileset(std::string FileLocation, int TileWidth, int TileHeight, int TilesetWidth, int TilesetHeight);
    Tileset() {};
    virtual ~Tileset();

    void ConfigureTileset(std::string FileLocation, int TileWidth, int TileHeight, int TilesetWidth, int TilesetHeight)
    {
        LoadTileset(FileLocation);

        SetTilePixelWidth(TileWidth);
        SetTilePixelHeight(TileHeight);

        SetTilesetPixelWidth(TilesetWidth);
        SetTilesetPixelHeight(TilesetHeight);

        WidthInCells = TilesetWidth / TileWidth;
        HeightInCells = TilesetHeight / TileHeight;
    }

    int GetTilePixelWidth()
    {
        return TilePixelWidth;
    }

    void SetTilePixelWidth(int val)
    {
        TilePixelWidth = val;
    }

    int GetTilePixelHeight()
    {
        return TilePixelHeight;
    }

    void SetTilePixelHeight(int val)
    {
        TilePixelHeight = val;
    }

    int GetTilesetPixelWidth()
    {
        return TilesetPixelWidth;
    }

    void SetTilesetPixelWidth(int val)
    {
        TilesetPixelWidth = val;
    }

    int GetTilesetPixelHeight()
    {
        return TilesetPixelHeight;
    }

    void SetTilesetPixelHeight(int val)
    {
        TilesetPixelHeight = val;
    }

    int GetWidthInCells()
    {
        return WidthInCells;
    }

    void SetWidthInCells(int val)
    {
        WidthInCells = val;
    }

    int GetHeightInCells()
    {
        return HeightInCells;
    }

    void SetHeightInCells(int val)
    {
        HeightInCells = val;
    }

    char GetTilesetName()
    {
        return TilesetName;
    }

    void SetTilesetName(char val)
    {
        TilesetName = val;
    }

    char GetTilesetDescription()
    {
        return TilesetDescription;
    }

    void SetTilesetDescription(char val)
    {
        TilesetDescription = val;
    }

    bool LoadTileset(std::string FileLocation);


    void AddTile();
    void RemoveTile();
    void CalculateVariables();

    sf::IntRect GetCellBounds(int Cell);

    sf::Texture TilesetTexture;

protected:

private:
    int TilePixelWidth;
    int TilePixelHeight;

    int TilesetPixelWidth;
    int TilesetPixelHeight;

    int WidthInCells;
    int HeightInCells;

    char TilesetName;
    char TilesetDescription;

    int CurrentIndexKey;

    struct VarState //Checks to see if the variables need to be calculated, if they are given by the tileset author, then they will not have to be calculated. !!OBSOLETE!!
    {
        bool CalculateTPW = 1;
        bool CalculateTPH = 1;
        bool CalculateTSPW = 1;
        bool CalculateTSPH = 1;
        bool CalculateWIT = 1;
        bool CalculateHIT = 1;
    };
};
