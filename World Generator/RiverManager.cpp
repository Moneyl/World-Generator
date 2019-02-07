#include "GameMap.h"

bool MapSystem::RiverManager::ContainedStartPoint(int Position)
{
    for( std::vector <int>::iterator CurrentVectorPos = RiverStartPoints.begin();
            CurrentVectorPos != RiverStartPoints.end(); CurrentVectorPos ++)
        if( (*CurrentVectorPos) == Position)
            return 1;
    return 0;
}

int MapSystem::RiverManager::ClosestWaterPosition(int Position)
{
    int LeftPosition = Position;
    int RightPosition = Position;
    int AbovePosition = Position;
    int BelowPosition = Position;
    /*int UpperLeftPosition = Position;
    int UpperRightPosition = Position;
    int LowerLeftPosition = Position;
    int LowerRightPosition = Position;*/

    int ShortestDistance = 1000000;
    bool exitvar = 0;

    while(exitvar == 0)
    {
        LeftPosition = CurrentMap->data[LeftPosition].Left();

        if(LeftPosition == -1)
        {
            exitvar = 1;
        }
        if(LeftPosition != -1)
        {
            if(CurrentMap->data[LeftPosition].z < CurrentMap->SeaLevel)
            {
                exitvar = 1;
            }
        }
    }

    exitvar = 0;

    while(exitvar == 0)
    {
        RightPosition = CurrentMap->data[RightPosition].Right();

        if(RightPosition == -1)
        {
            exitvar = 1;
        }
        if(RightPosition != -1)
        {
            if(CurrentMap->data[RightPosition].z < CurrentMap->SeaLevel)
            {
                exitvar = 1;
            }
        }
    }

    exitvar = 0;

    while(exitvar == 0)
    {
        AbovePosition = CurrentMap->data[AbovePosition].Above();

        if(AbovePosition == -1)
        {
            exitvar = 1;
        }
        if(AbovePosition != -1)
        {
            if(CurrentMap->data[AbovePosition].z < CurrentMap->SeaLevel)
            {
                exitvar = 1;
            }
        }
    }

    exitvar = 0;

    while(exitvar == 0)
    {
        BelowPosition = CurrentMap->data[BelowPosition].Below();

        if(BelowPosition == -1)
        {
            exitvar = 1;
        }
        if(BelowPosition != -1)
        {
            if(CurrentMap->data[BelowPosition].z < CurrentMap->SeaLevel)
            {
                exitvar = 1;
            }
        }
    }

    int LeftDistance = -1;
    int RightDistance = -1;
    int AboveDistance = -1;
    int BelowDistance = -1;

    if(LeftPosition >= 0 && LeftPosition <= CurrentMap->x * CurrentMap->y)
    {
        LeftDistance = CurrentMap->GetDistance(Position, LeftPosition);
    }
    if(RightPosition >= 0 && RightPosition <= CurrentMap->x * CurrentMap->y)
    {
        RightDistance = CurrentMap->GetDistance(Position, RightPosition);
    }
    if(AbovePosition >= 0 && AbovePosition <= CurrentMap->x * CurrentMap->y)
    {
        AboveDistance = CurrentMap->GetDistance(Position, AbovePosition);
    }
    if(BelowPosition >= 0 && BelowPosition <= CurrentMap->x * CurrentMap->y)
    {
        BelowDistance = CurrentMap->GetDistance(Position, BelowPosition);
    }

    if(LeftDistance >= 0)
    {
        if(LeftDistance > ShortestDistance)
        {
            ShortestDistance = LeftDistance;
        }
    }
    if(RightDistance >= 0)
    {
        if(RightDistance > ShortestDistance)
        {
            ShortestDistance = RightDistance;
        }
    }
    if(AboveDistance >= 0)
    {
        if(AboveDistance > ShortestDistance)
        {
            ShortestDistance = AboveDistance;
        }
    }
    if(BelowDistance >= 0)
    {
        if(BelowDistance > ShortestDistance)
        {
            ShortestDistance = BelowDistance;
        }
    }

    return ShortestDistance;

    /*if(Position > -1)
    {
        int ShortestDistance = -1;
        int MapSize = (CurrentMap->x * CurrentMap->y) - 1;

        int aLeft = CurrentMap->data[Position].Left();
        int aRight = CurrentMap->data[Position].Right();
        int aAbove = CurrentMap->data[Position].Above();
        int aBelow = CurrentMap->data[Position].Below();
        int aUpperLeft = CurrentMap->data[Position].UpperLeft();
        int aUpperRight = CurrentMap->data[Position].UpperRight();
        int aLowerLeft = CurrentMap->data[Position].LowerLeft();
        int aLowerRight = CurrentMap->data[Position].LowerRight();

        int PositionOfClosestPoint;

        for(int i = 0; i < CurrentWRM->ContainedRegions.size(); i++)
        {
            if(CurrentWRM->ContainedRegions[i].ContainedCoordinates.size() >= MinimumTargetSize)
            {
                int x1 = Position % CurrentMap->x;
                int y1 = Position / CurrentMap->x;

                int x2 = CurrentWRM->ContainedRegions[i].AbsoluteMidpointPosition % CurrentMap->x;
                int y2 = CurrentWRM->ContainedRegions[i].AbsoluteMidpointPosition / CurrentMap->x;

                int x3 = pow(x2 - x1, 2);
                int y3 = pow(y2 - y1, 2);

                int Distance = sqrt(x3 + y3);
                if(ShortestDistance != -1)
                {
                    if(Distance < ShortestDistance)
                    {
                        ShortestDistance = Distance;
                        PositionOfClosestPoint = CurrentWRM->ContainedRegions[i].AbsoluteMidpointPosition;
                    }
                }
                if(ShortestDistance == -1)
                {
                    ShortestDistance = Distance;
                    PositionOfClosestPoint = CurrentWRM->ContainedRegions[i].AbsoluteMidpointPosition;
                }
            }
        }

        if(ShortestDistance > -1)
        {
            return PositionOfClosestPoint;
        }
        else if(ShortestDistance == -1)
        {
            return -1;
        }
    }

    else if(Position == -1)
    {
        return -1;
    }*/
}

bool MapSystem::RiverManager::IsAdjacentToWater(int Position)
{
    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();
    /*int aUpperLeft = CurrentMap->data[Position].UpperLeft();
    int aUpperRight = CurrentMap->data[Position].UpperRight();
    int aLowerLeft = CurrentMap->data[Position].LowerLeft();
    int aLowerRight = CurrentMap->data[Position].LowerRight();*/

    if(aLeft > -1)
    {
        if(CurrentMap->data[aLeft].z <= CurrentMap->SeaLevel)
        {
            return 1;
        }
    }
    if(aRight > -1)
    {
        if(CurrentMap->data[aRight].z <= CurrentMap->SeaLevel)
        {
            return 1;
        }
    }
    if(aAbove > -1)
    {
        if(CurrentMap->data[aAbove].z <= CurrentMap->SeaLevel)
        {
            return 1;
        }
    }
    if(aBelow > -1)
    {
        if(CurrentMap->data[aBelow].z <= CurrentMap->SeaLevel)
        {
            return 1;
        }
    }
    return 0;
}

int MapSystem::RiverManager::ClosestStartPoint(int Position)
{
    if(RiverStartPoints.size() > 1)
    {
        int closestpoint = -1;

        for(int i = 0; i < RiverStartPoints.size(); i++)
        {
            int x1 = Position % CurrentMap->x;
            int y1 = Position / CurrentMap->y;

            int x2 = RiverStartPoints[i] % CurrentMap->x;
            int y2 = RiverStartPoints[i] / CurrentMap->x;

            int x3 = (int)pow(x2 - x1, 2);
            int y3 = (int)pow(y2 - y1, 2);

            int Distance = (int)sqrt(x3 + y3);
            if(closestpoint != -1)
            {
                if(Distance < closestpoint)
                {
                    closestpoint = Distance;
                }
            }
            if(closestpoint == -1)
            {
                closestpoint = Distance;
            }

        }

        //std::cout << "\nClosest Point: " << closestpoint;

        return closestpoint;
    }
    return -1;
}

int MapSystem::RiverManager::PickStartPosition()
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/PickStartPosition.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    int MapX = CurrentMap->x;
    int MapY = CurrentMap->y;
    int MapSize = (MapX * MapY) - 1;

    bool exit = false;
    int num = 0;
    CurrentCount = 0.01f;
    int Counter = 0;

    while(!exit)
    {
        srand((unsigned int)time(0));
        float TempVar = rand() * CurrentCount;
        float TempVar2 = rand() * TempVar * CurrentCount;
        int TempVar3 = static_cast<int>(floorf(TempVar2));

        num = TempVar3 % MapSize + 1;

        if(num >= 0 && num <= MapSize)
        {
            if(CurrentMap->data[num].z > CurrentMap->SeaLevel)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[num].x, CurrentMap->data[num].y) == 0 && CurrentMap->IsSide(CurrentMap->data[num].x, CurrentMap->data[num].y) == 0)
                {
                    if(ContainedStartPoint(num) == 0)
                    {
                        //fout << "\nClosest Start Point: " << ClosestStartPoint(num);

                        if(ClosestStartPoint(num) != -1)
                        {
                            if(ClosestStartPoint(num) >= MinimumSeparationDistance)
                            {
                                if(IsAdjacentToWater(num) == 0)
                                {
                                    exit = 1;
                                }
                            }
                        }
                        else if(ClosestStartPoint(num) <= -1)
                        {
                            if(IsAdjacentToWater(num) == 0)
                            {
                                exit = 1;
                            }
                        }
                    }
                }
            }
        }
        if(num > MapSize)
        {
            CurrentCount = 0.01f;
        }
        if(Counter > 10000)
        {
            num = -1;
            exit = 1;
        }

        Counter++;
        CurrentCount += 0.01f;
    }

    //fout << "\nStart Point Chosen: " << num;
    return num;
}

int MapSystem::RiverManager::NextPosition(int Position, bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/RiverNextPosition.txt";
    std::ofstream fout(FileName, std::ios::app);

    if(DebugMessages)
    {
        fout << "\n\n~~~FINDING NEXT POSITION~~~";
    }

    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();
    /*int aUpperLeft = CurrentMap->data[Position].UpperLeft();
    int aUpperRight = CurrentMap->data[Position].UpperRight();
    int aLowerLeft = CurrentMap->data[Position].LowerLeft();
    int aLowerRight = CurrentMap->data[Position].LowerRight();*/

    int CurrentHeight = CurrentMap->data[Position].z;
    int aNextPosition;
    int NextPositionHeight = CurrentHeight;

    if(ContainedRivers[CurrentRiver].Contains(aLeft) == 0)
    {
        //fout << "\nVal being passed to function below: " << aLeft;
        //fout << "\nIsAdjacentToSelf()-Left Return: " << ContainedRivers[CurrentRiver].IsAdjacentToSelf(aLeft);
        if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aLeft) == 0)
        {
            if(aLeft > -1)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0)
                {
                    if(CurrentMap->data[aLeft].z < NextPositionHeight)
                    {
                        NextPositionHeight = CurrentMap->data[aLeft].z;
                        aNextPosition = aLeft;
                    }
                }
            }
        }
    }
    if(ContainedRivers[CurrentRiver].Contains(aRight) == 0)
    {
        if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aRight) == 0)
        {

            if(aRight > -1)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0)
                {
                    if(CurrentMap->data[aRight].z < NextPositionHeight)
                    {
                        NextPositionHeight = CurrentMap->data[aRight].z;
                        aNextPosition = aRight;
                    }
                }
            }
        }
    }
    if(ContainedRivers[CurrentRiver].Contains(aAbove) == 0)
    {
        if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aAbove) == 0)
        {
            if(aAbove > -1)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0)
                {
                    if(CurrentMap->data[aAbove].z < NextPositionHeight)
                    {
                        NextPositionHeight = CurrentMap->data[aAbove].z;
                        aNextPosition = aAbove;
                    }
                }
            }
        }
    }
    if(ContainedRivers[CurrentRiver].Contains(aBelow) == 0)
    {
        if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aBelow) == 0)
        {
            if(aBelow > -1)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0)
                {
                    if(CurrentMap->data[aBelow].z < NextPositionHeight)
                    {
                        NextPositionHeight = CurrentMap->data[aBelow].z;
                        aNextPosition = aBelow;
                    }
                }
            }
        }
    }

    if(NextPositionHeight < CurrentHeight)
    {

        //fout << "\nNext Position Returned: " << aNextPosition << "\n\n";
        return aNextPosition;




    }
    else if(NextPositionHeight == CurrentHeight)
    {
        //fout << "\nNext Position Returned: -1";
        return -1; //Signifies that it must steam roll the thing.
    }


}

int MapSystem::RiverManager::RandomDirection(int Position, int RestrictedDirection)
{
    bool exit = 0;

    bool HitLeft = 0;
    bool HitRight = 0;
    bool HitAbove = 0;
    bool HitBelow = 0;

    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();

    bool LeftSelected = 0;
    bool RightSelected = 0;
    bool AboveSelected = 0;
    bool BelowSelected = 0;

    bool AllHit = 0;

    while(exit == 0)
    {
        srand((unsigned)time(0));
        float TempVar = rand() * Modifier;
        //float TempVar2 = TempVar;
        int num = static_cast<int> (TempVar) % 4 + 1;
        //fout << "\nRandom Direction: " << num;



        if(num == 1)
        {
            HitLeft = 1;
            if(RestrictedDirection != 1)
            {
                if(ContainedRivers[CurrentRiver].NoLeft == 0)
                {
                    if(CurrentMap->data[Position].Left() > -1)
                    {
                        if(ContainedRivers[CurrentRiver].Contains(aLeft) == 0)
                        {
                            if(CurrentMap->IsCorner(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0)
                            {
                                if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(CurrentMap->data[Position].Left()) == 0)
                                {
                                    //fout << "\nRandom Direction: " << CurrentMap->data[Position].Left();
                                    LeftSelected = 1;
                                    exit = 1;
                                    //return CurrentMap->data[Position].Left();
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(num == 2)
        {
            HitRight = 1;
            if(RestrictedDirection != 2)
            {
                if(ContainedRivers[CurrentRiver].NoRight == 0)
                {
                    if(CurrentMap->data[Position].Right() > -1)
                    {
                        if(ContainedRivers[CurrentRiver].Contains(aRight) == 0)
                        {
                            if(CurrentMap->IsCorner(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0)
                            {
                                if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(CurrentMap->data[Position].Right()) == 0)
                                {
                                    //fout << "\nRandom Direction: " << CurrentMap->data[Position].Right();
                                    RightSelected = 1;
                                    exit = 1;
                                    //return CurrentMap->data[Position].Right();
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(num == 3)
        {
            HitAbove = 1;
            if(RestrictedDirection != 3)
            {
                if(ContainedRivers[CurrentRiver].NoUp == 0)
                {
                    if(CurrentMap->data[Position].Above() > -1)
                    {
                        if(ContainedRivers[CurrentRiver].Contains(aAbove) == 0)
                        {
                            if(CurrentMap->IsCorner(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0)
                            {
                                if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(CurrentMap->data[Position].Above()) == 0)
                                {
                                    //fout << "\nRandom Direction: " << CurrentMap->data[Position].Above();
                                    AboveSelected = 1;
                                    exit = 1;
                                    //return CurrentMap->data[Position].Above();
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(num == 4)
        {
            HitBelow = 1;
            if(RestrictedDirection != 4)
            {
                if(ContainedRivers[CurrentRiver].NoDown == 0)
                {
                    if(CurrentMap->data[Position].Below() > -1)
                    {
                        if(ContainedRivers[CurrentRiver].Contains(aBelow) == 0)
                        {
                            if(CurrentMap->IsCorner(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0)
                            {
                                if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(CurrentMap->data[Position].Below()) == 0)
                                {
                                    //fout << "\nRandom Direction: " << CurrentMap->data[Position].Below();
                                    BelowSelected = 1;
                                    exit = 1;
                                    //return CurrentMap->data[Position].Below();
                                }
                            }
                        }
                    }
                }
            }
        }

        if(num <= (CurrentMap->x * CurrentMap->y) - 1)
        {
            Modifier += 0.01f;
        }
        else if(num > (CurrentMap->x * CurrentMap->y) - 1)
        {
            Modifier = 0.01f;
        }
        if(LeftSelected != 1 && RightSelected != 1 && AboveSelected != 1 && BelowSelected != 1)
        {
            if(HitLeft == 1 && HitRight == 1 && HitAbove == 1 && HitBelow == 1)
            {
                AllHit = 1;
                exit = 1;
            }
        }


    }
    if(AllHit == 1)
    {
        // std::cout << "\nRandom Direction Hit Dead End.";
        return -1;
    }

    if(BelowSelected == 1)
    {
        //std::cout << "\nRandom Direction Returned Below.";
        return CurrentMap->data[Position].Below();
    }
    if(LeftSelected == 1)
    {
        //std::cout << "\nRandom Direction Returned Left.";
        return CurrentMap->data[Position].Left();
    }
    if(RightSelected == 1)
    {
        //std::cout << "\nRandom Direction Returned Right.";
        return CurrentMap->data[Position].Right();
    }
    if(AboveSelected == 1)
    {
        //std::cout << "\nRandom Direction Returned Above.";
        return CurrentMap->data[Position].Above();
    }


}

bool MapSystem::RiverManager::SurroundedByObstacles(int Position)
{
    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();

    int LeftHeight;// = CurrentMap->data[aLeft].z;
    int RightHeight;// = CurrentMap->data[aRight].z;
    int AboveHeight;// = CurrentMap->data[aAbove].z;
    int BelowHeight;//= CurrentMap->data[aBelow].z;

    if(aLeft > -1)
    {
        LeftHeight = CurrentMap->data[aLeft].z;
    }
    else if(aLeft <= -1)
    {
        LeftHeight = -1;
    }

    if(aRight > -1)
    {
        RightHeight = CurrentMap->data[aRight].z;
    }
    else if(aRight <= -1)
    {
        RightHeight = -1;
    }

    if(aAbove > -1)
    {
        AboveHeight = CurrentMap->data[aAbove].z;
    }
    else if(aAbove <= -1)
    {
        AboveHeight = -1;
    }

    if(aBelow > -1)
    {
        BelowHeight = CurrentMap->data[aBelow].z;
    }
    else if(aBelow <= -1)
    {
        BelowHeight = -1;
    }

    int CurrentPositionHeight = CurrentMap->data[Position].z;

    bool LeftTrue = 0;
    bool RightTrue = 0;
    bool AboveTrue = 0;
    bool BelowTrue = 0;

    bool AllTrue = 0;

    if(aLeft > -1)
    {
        if(LeftHeight > -1)
        {
            if(CurrentPositionHeight < LeftHeight)
            {
                LeftTrue = 1;
            }
        }
        else if(LeftHeight <= -1)
        {
            LeftTrue = 1;
        }
    }

    if(aRight > -1)
    {
        if(RightHeight > -1)
        {
            if(CurrentPositionHeight < RightHeight)
            {
                RightTrue = 1;
            }
        }
        else if(RightHeight <= -1)
        {
            RightTrue = 1;
        }
    }

    if(aAbove > -1)
    {
        if(AboveHeight > -1)
        {
            if(CurrentPositionHeight < AboveHeight)
            {
                AboveTrue = 1;
            }
        }
        else if(AboveHeight <= -1)
        {
            AboveTrue = 1;
        }
    }

    if(aBelow > -1)
    {
        if(BelowHeight > -1)
        {
            if(CurrentPositionHeight < BelowHeight)
            {
                BelowTrue = 1;
            }
        }
        else if(BelowHeight <= -1)
        {
            BelowTrue = 1;
        }
    }

    if(LeftTrue == 1 && RightTrue == 1 && AboveTrue == 1 && BelowTrue == 1)
    {
        AllTrue = 1;
    }
    if(AllTrue == 1)
    {
        return 1;
    }
    else if(AllTrue == 0)
    {
        return 0;
    }


}

bool MapSystem::RiverManager::SurroundedByMountains(int Position)
{
    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();

    int LeftHeight;// = CurrentMap->data[aLeft].z;
    int RightHeight;// = CurrentMap->data[aRight].z;
    int AboveHeight;// = CurrentMap->data[aAbove].z;
    int BelowHeight;//= CurrentMap->data[aBelow].z;

    if(aLeft > -1)
    {
        LeftHeight = CurrentMap->data[aLeft].z;
    }
    else if(aLeft <= -1)
    {
        LeftHeight = -1;
    }

    if(aRight > -1)
    {
        RightHeight = CurrentMap->data[aRight].z;
    }
    else if(aRight <= -1)
    {
        RightHeight = -1;
    }

    if(aAbove > -1)
    {
        AboveHeight = CurrentMap->data[aAbove].z;
    }
    else if(aAbove <= -1)
    {
        AboveHeight = -1;
    }

    if(aBelow > -1)
    {
        BelowHeight = CurrentMap->data[aBelow].z;
    }
    else if(aBelow <= -1)
    {
        BelowHeight = -1;
    }

    //int CurrentPositionHeight = CurrentMap->data[Position].z;

    bool LeftTrue = 0;
    bool RightTrue = 0;
    bool AboveTrue = 0;
    bool BelowTrue = 0;

    bool AllTrue = 0;

    if(aLeft > -1)
    {
        if(LeftHeight > -1)
        {
            if(LeftHeight >= CurrentMap->MountainLevel)
            {
                LeftTrue = 1;
            }
        }
        else if(LeftHeight <= -1)
        {
            LeftTrue = 1;
        }
    }

    if(aRight > -1)
    {
        if(RightHeight > -1)
        {
            if(RightHeight >= CurrentMap->MountainLevel)
            {
                RightTrue = 1;
            }
        }
        else if(RightHeight <= -1)
        {
            RightTrue = 1;
        }
    }

    if(aAbove > -1)
    {
        if(AboveHeight > -1)
        {
            if(AboveHeight >= CurrentMap->MountainLevel)
            {
                AboveTrue = 1;
            }
        }
        else if(AboveHeight <= -1)
        {
            AboveTrue = 1;
        }
    }

    if(aBelow > -1)
    {
        if(BelowHeight > -1)
        {
            if(BelowHeight >= CurrentMap->MountainLevel)
            {
                BelowTrue = 1;
            }
        }
        else if(BelowHeight <= -1)
        {
            BelowTrue = 1;
        }
    }

    if(LeftTrue == 1 && RightTrue == 1 && AboveTrue == 1 && BelowTrue == 1)
    {
        AllTrue = 1;
    }
    if(AllTrue == 1)
    {
        return 1;
    }
    else if(AllTrue == 0)
    {
        return 0;
    }
}

int MapSystem::RiverManager::TestPositionFinder(int Position)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/TestPositionFinder.txt";
    std::ofstream fout(FileName, std::ios::app);

    //std::cout << "\n\nValue Passed To TestPositionFinder(): " << Position;
    int aLeft = CurrentMap->data[Position].Left();
    int aRight = CurrentMap->data[Position].Right();
    int aAbove = CurrentMap->data[Position].Above();
    int aBelow = CurrentMap->data[Position].Below();

    int LeftHeight;// = CurrentMap->data[aLeft].z;
    int RightHeight;// = CurrentMap->data[aRight].z;
    int AboveHeight;// = CurrentMap->data[aAbove].z;
    int BelowHeight;// = CurrentMap->data[aBelow].z;

    if(aLeft > -1)
    {
        LeftHeight = CurrentMap->data[aLeft].z;
    }
    else if(aLeft <= -1)
    {
        LeftHeight = -1;
    }

    if(aRight > -1)
    {
        RightHeight = CurrentMap->data[aRight].z;
    }
    else if(aRight <= -1)
    {
        RightHeight = -1;
    }

    if(aAbove > -1)
    {
        AboveHeight = CurrentMap->data[aAbove].z;
    }
    else if(aAbove <= -1)
    {
        AboveHeight = -1;
    }

    if(aBelow > -1)
    {
        BelowHeight = CurrentMap->data[aBelow].z;
    }
    else if(aBelow <= -1)
    {
        BelowHeight = -1;
    }

    bool LeftIsObstacle; //Check for invalids!
    bool RightIsObstacle;
    bool AboveIsObstacle;
    bool BelowIsObstacle;

    int LowestNonMontHeight = 500;
    int LowestNonMontPos = -1;

    int LowestMontHeight = 500;
    int LowestMontPos = -1;

    //int CurrentPositionHeight = CurrentMap->data[Position].z;
    //std::cout << "\n" << ContainedRivers[CurrentRiver].IsAdjacentToSelf(aLeft);
    if(aLeft > -1)
    {
        if(ContainedRivers[CurrentRiver].NoLeft == 0)
        {
            //std::cout << "\nLeft Contained Result: " << ContainedRivers[CurrentRiver].Contains(aLeft);
            if(ContainedRivers[CurrentRiver].Contains(aLeft) == 0)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aLeft].x, CurrentMap->data[aLeft].y) == 0)
                {
                    if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aLeft) == 0)
                    {
                        if(LeftHeight > -1)
                        {
                            if(LeftHeight < CurrentMap->MountainLevel)
                            {
                                if(LeftHeight < LowestNonMontHeight)
                                {
                                    LowestNonMontHeight = LeftHeight;
                                    LowestNonMontPos = aLeft;
                                }
                                if(LowestNonMontPos == -1)
                                {
                                    LowestNonMontPos = aLeft;
                                    LowestNonMontHeight = LeftHeight;
                                }
                            }
                            else if(LeftHeight >= CurrentMap->MountainLevel)
                            {
                                LeftIsObstacle = 1;
                                if(LeftHeight < LowestMontHeight)
                                {
                                    LowestMontHeight = LeftHeight;
                                    LowestMontPos = aLeft;
                                }
                                if(LowestMontPos == -1)
                                {
                                    LowestMontPos = aLeft;
                                    LowestMontHeight = LeftHeight;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "\n" << ContainedRivers[CurrentRiver].IsAdjacentToSelf(aRight);
    if(aRight > -1)
    {
        if(ContainedRivers[CurrentRiver].NoRight == 0)
        {
            //std::cout << "\nRight Contained Result: " << ContainedRivers[CurrentRiver].Contains(aRight);
            if(ContainedRivers[CurrentRiver].Contains(aRight) == 0)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aRight].x, CurrentMap->data[aRight].y) == 0)
                {
                    if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aRight) == 0)
                    {
                        if(RightHeight > -1)
                        {
                            if(RightHeight < CurrentMap->MountainLevel)
                            {
                                if(RightHeight < LowestNonMontHeight)
                                {
                                    LowestNonMontHeight = RightHeight;
                                    LowestNonMontPos = aRight;
                                }
                                if(LowestNonMontPos == -1)
                                {
                                    LowestNonMontPos = aRight;
                                    LowestNonMontHeight = RightHeight;
                                }
                            }
                            else if(RightHeight >= CurrentMap->MountainLevel)
                            {
                                RightIsObstacle = 1;
                                if(RightHeight < LowestMontHeight)
                                {
                                    LowestMontHeight = RightHeight;
                                    LowestMontPos = aRight;
                                }
                                if(LowestMontPos == -1)
                                {
                                    LowestMontPos = aRight;
                                    LowestMontHeight = RightHeight;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "\n" << ContainedRivers[CurrentRiver].IsAdjacentToSelf(aAbove);
    if(aAbove > -1)
    {
        if(ContainedRivers[CurrentRiver].NoUp == 0)
        {
            //std::cout << "\nAbove Contained Result: " << ContainedRivers[CurrentRiver].Contains(aAbove);
            if(ContainedRivers[CurrentRiver].Contains(aAbove) == 0)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aAbove].x, CurrentMap->data[aAbove].y) == 0)
                {
                    if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aAbove) == 0)
                    {
                        if(AboveHeight > -1)
                        {
                            if(AboveHeight < CurrentMap->MountainLevel)
                            {
                                if(AboveHeight < LowestNonMontHeight)
                                {
                                    LowestNonMontHeight = AboveHeight;
                                    LowestNonMontPos = aAbove;
                                }
                                if(LowestNonMontPos == -1)
                                {
                                    LowestNonMontPos = aAbove;
                                    LowestNonMontHeight = AboveHeight;
                                }
                            }
                            else if(AboveHeight >= CurrentMap->MountainLevel)
                            {
                                AboveIsObstacle = 1;
                                if(AboveHeight < LowestMontHeight)
                                {
                                    LowestMontHeight = AboveHeight;
                                    LowestMontPos = aAbove;
                                }
                                if(LowestMontPos == -1)
                                {
                                    LowestMontPos = aAbove;
                                    LowestMontHeight = AboveHeight;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "\n" << ContainedRivers[CurrentRiver].IsAdjacentToSelf(aBelow);
    if(aBelow > -1)
    {
        if(ContainedRivers[CurrentRiver].NoDown == 0)
        {
            //std::cout << "\nBelow Contained Result: " << ContainedRivers[CurrentRiver].Contains(aBelow);
            if(ContainedRivers[CurrentRiver].Contains(aBelow) == 0)
            {
                if(CurrentMap->IsCorner(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0 && CurrentMap->IsSide(CurrentMap->data[aBelow].x, CurrentMap->data[aBelow].y) == 0)
                {
                    if(ContainedRivers[CurrentRiver].IsAdjacentToSelf(aBelow) == 0)
                    {
                        if(BelowHeight > -1)
                        {
                            if(BelowHeight < CurrentMap->MountainLevel)
                            {
                                if(BelowHeight < LowestNonMontHeight)
                                {
                                    LowestNonMontHeight = BelowHeight;
                                    LowestNonMontPos = aBelow;
                                }
                                if(LowestNonMontPos == -1)
                                {
                                    LowestNonMontPos = aBelow;
                                    LowestNonMontHeight = BelowHeight;
                                }
                            }
                            else if(BelowHeight >= CurrentMap->MountainLevel)
                            {
                                BelowIsObstacle = 1;
                                if(BelowHeight < LowestMontHeight)
                                {
                                    LowestMontHeight = BelowHeight;
                                    LowestMontPos = aBelow;
                                }
                                if(LowestMontPos == -1)
                                {
                                    LowestMontPos = aBelow;
                                    LowestMontHeight = BelowHeight;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /*std::cout << "\n\nLowestMontHeight: " << LowestMontHeight;
    std::cout << "\nLowestMontPos: " << LowestMontPos;

    std::cout << "\nLowestNonMontHeight: " << LowestNonMontHeight;
    std::cout << "\nLowestNonMontPos: " << LowestNonMontPos;

    std::cout << "\nSurrounded By Obstacles Results: " << SurroundedByObstacles(Position);
    */
    if(LowestNonMontPos > -1)
    {
        //std::cout << "\nReturning LowestNonMontPos: " << LowestNonMontPos;
        return LowestNonMontPos;
    }
    /*if(LowestNonMontPos <= -1)
    {
        if(LowestMontPos > -1)
        {
            //std::cout << "\nReturning LowestMontPos: " << LowestMontPos;
            return LowestMontPos;
        }
    }*/
    if(LowestNonMontPos <= -1 && LowestMontPos <= -1)
    {
        //std::cout << "\nReturning -1: No Possible Directions, Dead End.";
        //std::cout << "\n";
        return -1;
    }
    else
    {
        return -1;
    }

    /*if(SurroundedByObstacles(Position) == 1)
    {
        if(LowestMontPos > -1)
        {
            fout << "\nReturning LowestMontPos: " << LowestMontPos;
            return LowestMontPos;
        }
    }
    if(SurroundedByObstacles(Position) == 0)
    {
        if(LowestNonMontPos > -1)
        {
            fout << "\nReturning LowestNonMontPos: " << LowestNonMontPos;
            return LowestNonMontPos;
        }
    }
     //if(LowestMontPos <= -1 && LowestNonMontPos <= -1)

        fout << "\nReturning -1: No Possible Directions, Dead End.";
        fout << "\n";
        return -1;
    */


}

void MapSystem::RiverManager::GenerateRivers(bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/RiverGeneration.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    if(DebugMessages)
    {
        fout << "~~~BEGINNING_OF_ENTRY~~~";
    }

    std::cout << "\n\nStarting River Generation...   ";

    sf::Clock FunctionTime;
    FunctionTime.restart();

    bool exita = 0;
    int i = 0;
    int StartPoint;
    int WaterEnds = 0;

    if(MaxRivers > 0)
    {
        while(exita == 0)
        {
            int exit = 0;

            int CurrentPosition;
            int aNextPosition;
            CurrentRiver = i;
            //fout << "\n\nCurrent River: " << i;

            StartPoint = PickStartPosition();

            if(StartPoint == -1)
            {
                exita = 1;
            }
            if(StartPoint > -1)
            {
                CurrentPosition = StartPoint;
                //std::cout << StartPoint;

                //fout << "\nStart Point: " << StartPoint;

                ContainedRivers.push_back(MapSystem::River());
                ContainedRivers[i].StartPos = StartPoint;

                RiverStartPoints.push_back(StartPoint);
                ContainedRivers[i].CurrentMap = CurrentMap;

                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition;
                //fout << "\nElevation of CurrentPos: " << CurrentMap->data[CurrentPosition].z;
                //ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                CurrentMap->data[CurrentPosition].IsRiver = 1;
                CurrentMap->data[StartPoint].IsRiverStartPoint = 1;
                int ArraySize = (CurrentMap->x * CurrentMap->y) - 1;
                LastMoveDirection = 0;

                int LeftCount = 0;
                int RightCount = 0;
                int UpCount = 0;
                int DownCount = 0;

                int StartPosX =  StartPoint % CurrentMap->x;
                int StartPosY = StartPoint / CurrentMap->x;

                int TargetWaterPos = ClosestWaterPosition(StartPoint);
                int TargetWaterX =  TargetWaterPos % CurrentMap->x;
                int TargetWaterY = TargetWaterPos / CurrentMap->x;

                if(DirectionRestrictions == 1)
                {
                    if(TargetWaterY < StartPosY && TargetWaterX < StartPosX)
                    {
                        if(TargetWaterY < StartPosY - MaximumVariance)
                        {
                            ContainedRivers[i].NoDown = 1;
                            ContainedRivers[i].NoRight = 1;
                        }
                        if(TargetWaterY >= StartPosY - MaximumVariance)
                        {
                            ContainedRivers[i].NoRight = 1;
                        }
                    }

                    if(TargetWaterY < StartPosY && TargetWaterX > StartPosX)
                    {
                        if(TargetWaterY < StartPosY - MaximumVariance)
                        {
                            ContainedRivers[i].NoDown = 1;
                            ContainedRivers[i].NoLeft = 1;
                        }
                        if(TargetWaterY >= StartPosY - MaximumVariance)
                        {
                            ContainedRivers[i].NoLeft = 1;
                        }
                    }
                    if(TargetWaterY > StartPosY && TargetWaterX < StartPosX)
                    {
                        if(TargetWaterY > StartPosY + MaximumVariance)
                        {
                            ContainedRivers[i].NoUp = 1;
                            ContainedRivers[i].NoRight = 1;
                        }
                        if(TargetWaterY <= StartPosY + MaximumVariance)
                        {
                            ContainedRivers[i].NoRight = 1;
                        }
                    }
                    if(TargetWaterY > StartPosY && TargetWaterX > StartPosX)
                    {
                        if(TargetWaterY > StartPosY + MaximumVariance)
                        {
                            ContainedRivers[i].NoUp = 1;
                            ContainedRivers[i].NoLeft = 1;
                        }
                        if(TargetWaterY <= StartPosY + MaximumVariance)
                        {
                            ContainedRivers[i].NoLeft = 1;
                        }
                    }
                }

                ContainedRivers[i].ContainedCoordinates.push_back(StartPoint);

                if(StartPoint != -1)
                {
                    while(exit == 0)
                    {
                        if(DebugMessages)
                        {
                            fout << "\nStart Position: " << StartPoint;
                            fout << "\nCurrent Position - X: " << CurrentMap->data[CurrentPosition].x << " Y: " << CurrentMap->data[CurrentPosition].y << " Z: " << CurrentMap->data[CurrentPosition].z;
                        }

                        if(CurrentMap->data[CurrentPosition].z > CurrentMap->SeaLevel)
                        {
                            if(SameMoveRestrictions == 0)
                            {
                                aNextPosition = TestPositionFinder(CurrentPosition);
                            }
                            else if(SameMoveRestrictions == 1)
                            {
                                if(LeftCount < MaximumSameMoveDirection && RightCount < MaximumSameMoveDirection && UpCount < MaximumSameMoveDirection && DownCount < MaximumSameMoveDirection)
                                {
                                    aNextPosition = TestPositionFinder(CurrentPosition);
                                }
                                else if(LeftCount >= MaximumSameMoveDirection)
                                {
                                    //aNextPosition = RandomDirection(CurrentPosition, 1);

                                    if(ContainedRivers[i].NoRight == 1 && ContainedRivers[i].NoUp == 1)
                                    {
                                        if(aNextPosition + CurrentMap->x <= ArraySize)
                                        {
                                            aNextPosition += CurrentMap->x;
                                        }
                                    }
                                    else
                                    {
                                        aNextPosition = RandomDirection(CurrentPosition, 1);
                                    }

                                    LeftCount = 0;
                                    RightCount = 0;
                                    UpCount = 0;
                                    DownCount = 0;

                                    if(aNextPosition == -1)
                                    {
                                        aNextPosition = TestPositionFinder(CurrentPosition);
                                    }
                                }
                                else if(RightCount >= MaximumSameMoveDirection)
                                {
                                    aNextPosition = RandomDirection(CurrentPosition, 2);

                                    LeftCount = 0;
                                    RightCount = 0;
                                    UpCount = 0;
                                    DownCount = 0;

                                    if(aNextPosition == -1)
                                    {
                                        aNextPosition = TestPositionFinder(CurrentPosition);
                                    }
                                }
                                else if(UpCount >= MaximumSameMoveDirection)
                                {
                                    aNextPosition = RandomDirection(CurrentPosition, 3);

                                    LeftCount = 0;
                                    RightCount = 0;
                                    UpCount = 0;
                                    DownCount = 0;

                                    if(aNextPosition == -1)
                                    {
                                        aNextPosition = TestPositionFinder(CurrentPosition);
                                    }
                                }
                                else if(DownCount >= MaximumSameMoveDirection)
                                {
                                    aNextPosition = RandomDirection(CurrentPosition, 4);

                                    LeftCount = 0;
                                    RightCount = 0;
                                    UpCount = 0;
                                    DownCount = 0;

                                    if(aNextPosition == -1)
                                    {
                                        aNextPosition = TestPositionFinder(CurrentPosition);
                                    }
                                }
                            }


                            ContainedRivers[i].ContainedCoordinates.push_back(aNextPosition);
                            int TempX1 = aNextPosition % CurrentMap->x;
                            int TempY1 = aNextPosition / CurrentMap->x;

                            if(TempX1 != 0 )
                            {
                                if(aNextPosition == CurrentPosition - 1)
                                {
                                    LastMoveDirection = 1; //Left.
                                    ContainedRivers[i].LastMoveDirection = 1;
                                    LeftCount++;
                                }
                            }
                            if(TempX1 != CurrentMap->x)
                            {
                                if(aNextPosition == CurrentPosition + 1)
                                {
                                    LastMoveDirection = 2; //Right.
                                    ContainedRivers[i].LastMoveDirection = 2;
                                    RightCount++;
                                }
                            }
                            if(TempY1 != 0)
                            {
                                if(aNextPosition == CurrentPosition - CurrentMap->x)
                                {
                                    LastMoveDirection = 3; //Up.
                                    ContainedRivers[i].LastMoveDirection = 3;
                                    UpCount++;
                                }
                            }
                            if(TempY1 != CurrentMap->y)
                            {
                                if(aNextPosition == CurrentPosition + CurrentMap->x)
                                {
                                    LastMoveDirection = 4; //Down.
                                    ContainedRivers[i].LastMoveDirection = 4;
                                    DownCount++;
                                }
                            }


                            //fout << "\nNextPosition: " << aNextPosition;
                            //fout << "\nArraySize: " << ArraySize;

                            //fout << "\nNext Position: " << aNextPosition << "\nContained: " << ContainedRivers[i].Contains(aNextPosition) << "\nIs Adjacent To Self: " << ContainedRivers[i].IsAdjacentToSelf(aNextPosition);

                            if(DebugMessages)
                            {
                                fout << "\nNext Position: " << aNextPosition;
                            }

                            if(aNextPosition > -1 && aNextPosition <= ArraySize)
                            {
                                if(IsAdjacentToWater(aNextPosition) == 0)
                                {
                                    if(CurrentMap->data[aNextPosition].IsRiver == 0)
                                    {
                                        if(CurrentMap->data[CurrentPosition].z >= CurrentMap->data[aNextPosition].z)
                                        {
                                            if(CurrentMap->data[aNextPosition].z > CurrentMap->SeaLevel)
                                            {
                                                CurrentMap->data[aNextPosition].IsRiver = 1;
                                                CurrentMap->data[aNextPosition].RiverID = i;
                                                ContainedRivers[i].ContainedCoordinates.push_back(aNextPosition);
                                                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition;
                                                ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                                CurrentPosition = aNextPosition;
                                            }
                                            else if(CurrentMap->data[aNextPosition].z <= CurrentMap->SeaLevel)
                                            {
                                                ContainedRivers[i].HitOcean = 1;
                                                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition;
                                                ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                                //fout << "\n!!!!EXIT!!!! Hit Ocean on Non Obstacle.";
                                                WaterEnds++;
                                                exit = 1;
                                            }
                                        }
                                        else if(CurrentMap->data[CurrentPosition].z < CurrentMap->data[aNextPosition].z)
                                        {
                                            if(CurrentMap->data[aNextPosition].z > CurrentMap->SeaLevel)
                                            {
                                                //int TempDifference =

                                                CurrentMap->data[aNextPosition].z = CurrentMap->data[CurrentPosition].z;
                                                CurrentMap->data[aNextPosition].RiverID = i;
                                                CurrentMap->data[aNextPosition].IsRiver = 1;
                                                ContainedRivers[i].ContainedCoordinates.push_back(aNextPosition);
                                                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition << "\nAbsolute of RandPos: " << aNextPosition;
                                                ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                                CurrentPosition = aNextPosition;
                                            }
                                            else if(CurrentMap->data[aNextPosition].z <= CurrentMap->SeaLevel)
                                            {
                                                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition << "\nAbsolute of RandPos: " << aNextPosition;
                                                ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                                ContainedRivers[i].HitOcean = 1;
                                                WaterEnds++;
                                                //fout << "\n!!!!EXIT!!!! Hit Ocean on Obstacle.";
                                                exit = 1;
                                            }

                                        }
                                    }
                                    else if(CurrentMap->data[aNextPosition].IsRiver == 1)
                                    {
                                        if(CurrentMap->data[aNextPosition].RiverID == i)
                                        {
                                            //fout << "\n!!!!NOT_GOOD!!!! - Hit Self Exit - RiverID: " << i;
                                            exit = 1;
                                        }
                                        else if(CurrentMap->data[aNextPosition].RiverID != i)
                                        {
                                            int OtherRiverID = CurrentMap->data[aNextPosition].RiverID;
                                            if(ContainedRivers[OtherRiverID].HitOcean == 1)
                                            {
                                                ContainedRivers[OtherRiverID].IsParent = 1;
                                                ContainedRivers[OtherRiverID].IsChild = 0;

                                                ContainedRivers[i].IsParent = 0;
                                                ContainedRivers[i].IsChild = 1;
                                                WaterEnds++;

                                                //fout << "\n!!!!EXIT!!!! Hit River That Has Hit Ocean.";
                                                exit = 1;
                                            }
                                            else if(ContainedRivers[OtherRiverID].HitOcean == 0)
                                            {
                                                ContainedRivers[OtherRiverID].IsParent = 0;
                                                ContainedRivers[OtherRiverID].IsChild = 1;

                                                ContainedRivers[i].IsParent = 1;
                                                ContainedRivers[i].IsChild = 0;
                                                ContainedRivers[i].AddAdjacentTiles(aNextPosition);
                                                CurrentPosition = aNextPosition;
                                            }
                                        }
                                    }
                                }
                                else if(IsAdjacentToWater(aNextPosition) == 1)
                                {
                                    //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition << "\nAbsolute of RandPos: " << aNextPosition;

                                    CurrentMap->data[aNextPosition].IsRiver = 1;
                                    CurrentMap->data[aNextPosition].RiverID = i;
                                    ContainedRivers[i].ContainedCoordinates.push_back(aNextPosition);

                                    ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                    ContainedRivers[i].AddAdjacentTiles(aNextPosition);
                                    ContainedRivers[i].HitOcean = 1;
                                    WaterEnds++;
                                    //fout << "\n!!!!EXIT!!!! Hit Ocean, Adjacent to Ocean.";
                                    exit = 1;
                                }

                            }

                            else if(aNextPosition <= -1)
                            {
                                //fout << "\nAbsolute of CurrentPos: " << CurrentPosition << "\nAbsolute of NextPos: " << aNextPosition << "\nAbsolute of RandPos: " << aNextPosition;
                                ContainedRivers[i].AddAdjacentTiles(CurrentPosition);
                                ContainedRivers[i].HitDeadEnd = 1;
                                //fout << "\n!!!!EXIT!!!! Hit Dead End.";
                                exit = 1;
                            }
                        }
                    }


                    /*else if(CurrentMap->data[CurrentPosition].z <= CurrentMap->SeaLevel)
                    {
                        ContainedRivers[i].HitOcean = 1;
                        exit = 1;
                    }*/
                }
                if(StartPoint != -1)
                {
                    if(i < MaxRivers)
                    {
                        i++;
                    }
                    else if(i >= MaxRivers)
                    {
                        exita = 1;
                    }
                }
                else if(StartPoint == -1)
                {
                    exita = 1;
                }
            }
        }
    }

    std::cout << "\n" << WaterEnds << " out of " << MaxRivers << " Rivers hit water.";

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";
}

void MapSystem::RiverManager::Reset()
{
    while(ContainedRivers.empty() == 0)
    {
        ContainedRivers.pop_back();
    }
    while(RiverStartPoints.empty() == 0)
    {
        RiverStartPoints.pop_back();
    }
    CurrentCount = 0.01f;
    Modifier = 0.01f;
}
