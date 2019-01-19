#include "GameMap.h"

bool MapSystem::HeightRegion::Contains(int XVal, int YVal)
{
    int ArrayPosition = CurrentMap->ConvertToAbsolute(XVal, YVal);

    for( std::vector <int>::iterator CurrentVectorPos = RegionCoordinateContainer.begin();
            CurrentVectorPos != RegionCoordinateContainer.end(); CurrentVectorPos ++)
        if( (*CurrentVectorPos) == ArrayPosition)
            return 1;
    return 0;
}
