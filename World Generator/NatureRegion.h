#include "CartesianCoordinate.h"


class NatureRegion
{
public:
    NatureRegion();
    ~NatureRegion();

    int CenterX;
    int CenterY;

    std::vector <CartesianCoordinate*> ContainedCoordinates;

    CartesianCoordinate* operator[](int arraypos)
    {
        return ContainedCoordinates[arraypos];
    }

};
