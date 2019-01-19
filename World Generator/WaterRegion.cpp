#include "GameMap.h"

bool MapSystem::WaterRegion::Contains(int XVal, int YVal)
{
    int ArrayPosition = CurrentMap->ConvertToAbsolute(XVal, YVal);

    for( std::vector <int>::iterator CurrentVectorPos = ContainedCoordinates.begin();
            CurrentVectorPos != ContainedCoordinates.end(); CurrentVectorPos ++)
        if( (*CurrentVectorPos) == ArrayPosition)
            return 1;
    return 0;
}

bool MapSystem::WaterRegion::Contains(int Position)
{
    for( std::vector <int>::iterator CurrentVectorPos = ContainedCoordinates.begin();
            CurrentVectorPos != ContainedCoordinates.end(); CurrentVectorPos ++)
        if( (*CurrentVectorPos) == Position)
            return 1;
    return 0;
}

void MapSystem::WaterRegion::CalculateMidpoints()
{
    int TempX1 = FurthestUpPosition % CurrentMap->x;
    int TempY1 = FurthestUpPosition / CurrentMap->x;

    int TempX2 = FurthestDownPosition % CurrentMap->x;
    int TempY2 = FurthestDownPosition / CurrentMap->x;

    int TempX3 = (TempX2 + TempX1) / 2;
    int TempY3 = (TempY2 + TempY1) / 2;

    UpDownMidpointPosition = CurrentMap->ConvertToAbsolute(TempX3, TempY3);

    TempX1 = FurthestLeftPosition % CurrentMap->x;
    TempY1 = FurthestLeftPosition / CurrentMap->x;

    TempX2 = FurthestRightPosition % CurrentMap->x;
    TempY2 = FurthestRightPosition / CurrentMap->x;

    TempX3 = (TempX2 + TempX1) / 2;
    TempY3 = (TempY2 + TempY1) / 2;

    LeftRightMidpointPosition = CurrentMap->ConvertToAbsolute(TempX3, TempY3);

    if(UpDownMidpointPosition != LeftRightMidpointPosition)
    {
        TempX1 = LeftRightMidpointPosition % CurrentMap->x;
        TempY1 = LeftRightMidpointPosition / CurrentMap->x;

        TempX2 = UpDownMidpointPosition % CurrentMap->x;
        TempY2 = UpDownMidpointPosition / CurrentMap->x;

        TempX3 = (TempX2 + TempX1) / 2;
        TempY3 = (TempY2 + TempY1) / 2;

        AbsoluteMidpointPosition = CurrentMap->ConvertToAbsolute(TempX3, TempY3);
    }
    else if(UpDownMidpointPosition == LeftRightMidpointPosition)
    {
        AbsoluteMidpointPosition = UpDownMidpointPosition;
    }

}
