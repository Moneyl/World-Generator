#include "Tileset.h"

Tileset::Tileset(std::string FileLocation, int TileWidth, int TileHeight, int TilesetWidth, int TilesetHeight)
{
    LoadTileset(FileLocation);

    SetTilePixelWidth(TileWidth);
    SetTilePixelHeight(TileHeight);

    SetTilesetPixelWidth(TilesetWidth);
    SetTilesetPixelHeight(TilesetHeight);

    WidthInCells = TilesetWidth / TileWidth;
    HeightInCells = TilesetHeight / TileHeight;


}

Tileset::~Tileset()
{

}

bool Tileset::LoadTileset(std::string FileLocation)
{
	if (TilesetTexture.loadFromFile(FileLocation))
	{
		return true;
	}
	return false;
}

void Tileset::AddTile()
{
    //TileIndex.insert()
}

void Tileset::RemoveTile()
{

}

void Tileset::CalculateVariables()
{

}

sf::IntRect Tileset::GetCellBounds(int Cell)
{

    sf::IntRect TempRect;

    bool endloop = 0;
    int CurrentRow = 0;

    do
        {
            if(Cell > (CurrentRow + 1) * (WidthInCells))
            {
                CurrentRow++;
            }

            else if(Cell <= (CurrentRow + 1) * (WidthInCells))
            {
                endloop = 1;
            }
        }
    while(endloop == 0);


    if(Cell > WidthInCells)
    {
        int CellDelta = 0;

        do
            if(CellDelta == 0)
            {
                CellDelta = Cell - WidthInCells;
            }

            else if(CellDelta > WidthInCells)
            {
                CellDelta -= WidthInCells;
            }

        while(CellDelta > WidthInCells);

        TempRect.left = (CellDelta - 1) * (TilePixelWidth); //FIX THIS!
        TempRect.top = CurrentRow * TilePixelHeight;
    }

    else if(Cell < WidthInCells)
    {
        TempRect.top = CurrentRow * TilePixelHeight;
        TempRect.left = Cell * TilePixelWidth; //FIX THIS!
    }

    TempRect.width = TilePixelWidth;
    TempRect.height = TilePixelHeight;

    return TempRect;
}
