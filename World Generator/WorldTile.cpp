#include "WorldTile.h"

WorldTile::~WorldTile()
{

}

int WorldTile::Left()
{
    if(x - 1 > -1)
    {
        return ConvertToAbsolute(x - 1, y);
    }
    return -1;
}

int WorldTile::Right()
{
    if(x + 1 <= MapWidth - 1)
    {
        return ConvertToAbsolute(x + 1, y);
    }
    return -1;
}

int WorldTile::Above()
{
    if(y - 1 > -1)
    {
        return ConvertToAbsolute(x, y - 1);
    }
    return -1;
}

int WorldTile::Below()
{
    if(y + 1 <= MapHeight - 1)
    {
        return ConvertToAbsolute(x, y + 1);
    }
    return -1;
}

int WorldTile::UpperLeft()
{
    if(y - 1 > -1 && x - 1 > -1)
    {
        return ConvertToAbsolute(x - 1, y - 1);
    }
    return -1;
}

int WorldTile::UpperRight()
{
    if(y - 1 > -1 && x + 1 <= MapWidth - 1)
    {
        return ConvertToAbsolute(x + 1, y - 1);
    }
    return -1;
}

int WorldTile::LowerLeft()
{
    if(y + 1 <= MapHeight - 1 && x - 1 > -1)
    {
        return ConvertToAbsolute(x - 1, y + 1);
    }
    return -1;
}

int WorldTile::LowerRight()
{
    if(y + 1 <= MapHeight - 1 && x + 1 <= MapWidth - 1)
    {
        return ConvertToAbsolute(x + 1, y + 1);
    }
    return -1;
}

bool WorldTile::IsBorderTile()//Returns simply if a tile is on the map border with no addition info, use the other functions for more useful returns.
{
    if(x == 0)
    {
        return 1;
    }
    if(y == 0)
    {
       return 1;
    }
    if(x == MapWidth + 1)
    {
        return 1;
    }
    if(y == MapHeight + 1)
    {
        return 1;
    }
    return 0;
}

int WorldTile::IsCorner()//Returns follow the corners clockwise, starting at the top left corner.
{
    if(x == 0 && y == 0)
    {
        return 1;//Top Left
    }
    else if(x == MapWidth - 1 && y == 0)
    {
        return 2;//Top Right
    }
    else if(x == MapWidth - 1 && y == MapHeight - 1)
    {
        return 3;//Bottom Right
    }
    else if(x == 0 && y == MapHeight - 1)
    {
        return 4;//Bottom Left
    }
    else
    {
        return 0;
    }
}

int WorldTile::IsSide()//Returns follow the sides clockwise, starting at the top side.
{
    if(y == 0)
    {
        if(x > 0 && x < MapWidth - 1)
        {
            return 1;//Top
        }
    }
    else if(x == MapWidth - 1)
    {
        if(y > 0 && y < MapHeight - 1)
        {
            return 2;//Right
        }
    }
    else if(y == MapHeight - 1)
    {
        if(x > 0 && x < MapWidth - 1)
        {
            return 3;//Bottom
        }
    }
    else if(x == 0)
    {
        if(y > 0 && y < MapHeight - 1)
        {
            return 4;//Left
        }
    }
    else
    {
        return 0;
    }
	return 0;
}
