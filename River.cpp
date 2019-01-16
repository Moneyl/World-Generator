#include "GameMap.h"


bool MapSystem::River::Contains(int XVal, int YVal)
{
    int ArrayPosition = CurrentMap->ConvertToAbsolute(XVal, YVal);

    for(std::vector <int>::iterator CurrentVectorPos = ContainedCoordinates.begin(); CurrentVectorPos != ContainedCoordinates.end(); CurrentVectorPos ++)
    {
        if((*CurrentVectorPos) == ArrayPosition)
        {
            return 1;
        }
    }
    return 0;
}

bool MapSystem::River::Contains(int Position)
{
    for(std::vector <int>::iterator CurrentVectorPos = ContainedCoordinates.begin(); CurrentVectorPos != ContainedCoordinates.end(); CurrentVectorPos++)
    {
        if((*CurrentVectorPos) == Position)
        {
            return 1;
        }
    }
    return 0;
}

void MapSystem::River::AddAdjacentTiles(int Position)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/AddAdjacentTiles.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    //std::cout << "\n\nCurrent Tile Being Processed:";
    //std::cout << "\nAbsolute: " << Position << " X: " << Position % CurrentMap->x << " Y: " << Position / CurrentMap->x << "\n";

    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();
    int aUpperLeft = CurrentMap->data[Position].UpperLeft();
    int aUpperRight = CurrentMap->data[Position].UpperRight();
    int aLowerLeft = CurrentMap->data[Position].LowerLeft();
    int aLowerRight = CurrentMap->data[Position].LowerRight();

    if(aLeft > -1)
    {
        if(CurrentMap->data[aLeft].IsRiver == 0)
        {
            if(IsAdjacentToSelf(aLeft) == 0)
            {
                AdjacentTiles.push_back(aLeft);
            }
        }
    }
    if(aRight > -1)
    {
        if(CurrentMap->data[aRight].IsRiver == 0)
        {
            if(IsAdjacentToSelf(aRight) == 0)
            {
                AdjacentTiles.push_back(aRight);
            }
        }
    }
    if(aAbove > -1)
    {
        if(CurrentMap->data[aAbove].IsRiver == 0)
        {
            if(IsAdjacentToSelf(aAbove) == 0)
            {
                AdjacentTiles.push_back(aAbove);
            }
        }
    }
    if(aBelow > -1)
    {
        if(CurrentMap->data[aBelow].IsRiver == 0)
        {
            if(IsAdjacentToSelf(aBelow) == 0)
            {
                AdjacentTiles.push_back(aBelow);
            }
        }
    }

    if(LastMoveDirection == 1)
    {
        if(aUpperRight > -1)
        {
            if(CurrentMap->data[aUpperRight].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aUpperRight) == 0)
                {
                    AdjacentTiles.push_back(aUpperRight);
                }
            }
        }

        if(aLowerRight > -1)
        {
            if(CurrentMap->data[aLowerRight].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aLowerRight) == 0)
                {
                    AdjacentTiles.push_back(aLowerRight);
                }
            }
        }
    }
    else if(LastMoveDirection == 2)
    {
        if(aUpperLeft > -1)
        {
            if(CurrentMap->data[aUpperLeft].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aUpperLeft) == 0)
                {
                    AdjacentTiles.push_back(aUpperLeft);
                }
            }
        }

        if(aLowerLeft > -1)
        {
            if(CurrentMap->data[aLowerLeft].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aLowerLeft) == 0)
                {
                    AdjacentTiles.push_back(aLowerLeft);
                }
            }
        }
    }
    else if(LastMoveDirection == 3)
    {
        if(aLowerLeft > -1)
        {
            if(CurrentMap->data[aLowerLeft].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aLowerLeft) == 0)
                {
                    AdjacentTiles.push_back(aLowerLeft);
                }
            }
        }

        if(aLowerRight > -1)
        {
            if(CurrentMap->data[aLowerRight].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aLowerRight) == 0)
                {
                    AdjacentTiles.push_back(aLowerRight);
                }
            }
        }
    }
    else if(LastMoveDirection == 4)
    {
        if(aUpperLeft > -1)
        {
            if(CurrentMap->data[aUpperLeft].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aUpperLeft) == 0)
                {
                    AdjacentTiles.push_back(aUpperLeft);
                }
            }
        }
        if(aUpperRight > -1)
        {
            if(CurrentMap->data[aUpperRight].IsRiver == 0)
            {
                if(IsAdjacentToSelf(aUpperRight) == 0)
                {
                    AdjacentTiles.push_back(aUpperRight);
                }
            }
        }
    }
}

bool MapSystem::River::IsAdjacentToSelf(int Position)
{
    for(std::vector <int>::iterator CurrentVectorPos = AdjacentTiles.begin(); CurrentVectorPos != AdjacentTiles.end(); CurrentVectorPos ++)
    {
        if((*CurrentVectorPos) == Position)
        {
            return 1;
        }
    }
    return 0;
}



