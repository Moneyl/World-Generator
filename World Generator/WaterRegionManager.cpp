#include "GameMap.h"

void MapSystem::WaterRegionManager::FlattenSmallWaterBodies()
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/WaterFlatten.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    //fout << "\nContained Regions Size: " << ContainedRegions.size();

    for(int i = 0; i < ContainedRegions.size(); i++)
    {
        //fout << "\n\nCurrent Region: " << i;
        //fout << "\nCurrent Region Size: " << ContainedRegions[i].ContainedCoordinates.size();
        //fout << "\nMinimum Water Body Size: " << MinimumWaterBodySize;

        if(ContainedRegions[i].ContainedCoordinates.size() < MinimumWaterBodySize)
        {
            //fout << "\nRegion Small Enough.";
            for(int a = 0; a < ContainedRegions[i].ContainedCoordinates.size(); a++)
            {
                int TempPos = ContainedRegions[i].ContainedCoordinates[a];
                //fout << "\nCurrent Pos Being Flattened- X: " << CurrentMap->data[TempPos].x << " Y: " << CurrentMap->data[TempPos].y;
                CurrentMap->data[TempPos].z = CurrentMap->SeaLevel + 10;
                CurrentMap->data[TempPos].FlattenedWater = 1;
            }
        }
    }
}

void MapSystem::WaterRegionManager::ClearWaterRegions()
{
    for(int i = 0; i < ContainedRegions.size(); i++)
    {
        for(int i2 = 0; i2 < ContainedRegions[i].ContainedCoordinates.size(); i2++)
        {
            CurrentMap->data[ContainedRegions[i].ContainedCoordinates[i2]].InWaterRegion = 0;
        }
    }

    while(ContainedRegions.empty() == 0)
    {
        ContainedRegions.pop_back();
    }
}

void MapSystem::WaterRegionManager::Reset()
{
    while(ContainedRegions.empty() == 0)
    {
        ContainedRegions.pop_back();
    }
}

void MapSystem::WaterRegionManager::CalculateWaterRegions(bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/WaterRegionDetection.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    if(DebugMessages)
    {
        fout << "~~~BEGINNING_OF_ENTRY~~~";
    }

    std::cout << "\n\nStarting Water Region Detection...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    int GridX = 0;
    int GridY = 0;

    int XLimit = CurrentMap->x - 1;
    int YLimit = CurrentMap->y - 1;

    std::queue <int> CoordinateQueue;

    int CurrentRegion = 0;


    while(GridX <= XLimit && GridY <= YLimit)
    {
        int TempArrayPos = CurrentMap->ConvertToAbsolute(GridX, GridY);


        if(CurrentMap->data[TempArrayPos].z <= CurrentMap->SeaLevel)
        {
            if(CurrentMap->data[TempArrayPos].InWaterRegion == 0)
            {
                CoordinateQueue.push(TempArrayPos);
                ContainedRegions.push_back(MapSystem::WaterRegion());
                ContainedRegions[CurrentRegion].CurrentMap = CurrentMap;
                ContainedRegions[CurrentRegion].AddCoordinate(TempArrayPos);

                CurrentMap->data[TempArrayPos].InWaterRegion = 1;
                if(ContainedRegions[CurrentRegion].FurthestLeftPosition == -1)
                {
                    ContainedRegions[CurrentRegion].FurthestLeftPosition = TempArrayPos;
                }
                else if(ContainedRegions[CurrentRegion].FurthestRightPosition == -1)
                {
                    ContainedRegions[CurrentRegion].FurthestRightPosition = TempArrayPos;
                }
                else if(ContainedRegions[CurrentRegion].FurthestUpPosition == -1)
                {
                    ContainedRegions[CurrentRegion].FurthestUpPosition = TempArrayPos;
                }
                else if(ContainedRegions[CurrentRegion].FurthestDownPosition == -1)
                {
                    ContainedRegions[CurrentRegion].FurthestDownPosition = TempArrayPos;
                }

                fout << "\n\nCurrent is Water- X: " << GridX << " Y: " << GridY << " Z: " << CurrentMap->data[TempArrayPos].z;

                while(CoordinateQueue.empty() == 0)
                {
                    if(DebugMessages)
                    {
                        fout << "\n\nQueue not empty.";
                    }

                    int CoordinatePos = CoordinateQueue.front();
                    if(DebugMessages)
                    {
                        //fout << "\nCoordinatePos: " << CoordinatePos;
                        //fout << "\nCoordinateQueue.front(): " << CoordinateQueue.front();
                    }

                    if(DebugMessages)
                    {
                        fout << "\nLOOP-TWO: " << "X: " << (CoordinatePos % CurrentMap->x) << " Y: " << (CoordinatePos / CurrentMap->x);
                        fout << "\nCurrentRegion: " << CurrentRegion;
                    }

                    int aLeft = CurrentMap->data[CoordinatePos].Left();
                    int aRight = CurrentMap->data[CoordinatePos].Right();
                    int aAbove = CurrentMap->data[CoordinatePos].Above();
                    int aBelow = CurrentMap->data[CoordinatePos].Below();

                    int LeftHeight = -1;
                    int RightHeight = -1;
                    int AboveHeight = -1;
                    int BelowHeight = -1;

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

                    if(DebugMessages)
                    {
                        fout << "\nLeft absolute value: " << aLeft;
                        fout << "\nLeft InWaterRegion: " << CurrentMap->data[aLeft].InWaterRegion;
                    }

                    if(aLeft > -1)
                    {
                        if(LeftHeight <= CurrentMap->SeaLevel)
                        {
                            if(CurrentMap->data[aLeft].InWaterRegion == 0)
                            {
                                CoordinateQueue.push(aLeft);
                                ContainedRegions[CurrentRegion].AddCoordinate(aLeft);
                                CurrentMap->data[aLeft].InWaterRegion = 1;

                                int TempX1 = aLeft % CurrentMap->x;
                                //int TempY1 = aLeft / CurrentMap->x;

                                int TempX2 = ContainedRegions[CurrentRegion].FurthestLeftPosition % CurrentMap->x;
                                //int TempY2 = ContainedRegions[CurrentRegion].FurthestLeftPosition / CurrentMap-> x;

                                if(ContainedRegions[CurrentRegion].FurthestLeftPosition != -1)
                                {
                                    if(TempX1 < TempX2)
                                    {
                                        ContainedRegions[CurrentRegion].FurthestLeftPosition = aLeft;
                                    }
                                }
                                else if(ContainedRegions[CurrentRegion].FurthestLeftPosition == -1)
                                {
                                    ContainedRegions[CurrentRegion].FurthestLeftPosition = aLeft;
                                }

                                if(DebugMessages)
                                {
                                    fout << "\nLeft Added.";
                                }

                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\nRight absolute value: " << aLeft;
                        fout << "\nRight InWaterRegion: " << CurrentMap->data[aLeft].InWaterRegion;
                    }

                    if(aRight > -1)
                    {
                        if(RightHeight <= CurrentMap->SeaLevel)
                        {
                            if(CurrentMap->data[aRight].InWaterRegion == 0)
                            {
                                CoordinateQueue.push(aRight);
                                ContainedRegions[CurrentRegion].AddCoordinate(aRight);
                                CurrentMap->data[aRight].InWaterRegion = 1;

                                int TempX1 = aRight % CurrentMap->x;
                                //int TempY1 = aRight / CurrentMap->x;

                                int TempX2 = ContainedRegions[CurrentRegion].FurthestRightPosition % CurrentMap->x;
                                //int TempY2 = ContainedRegions[CurrentRegion].FurthestRightPosition / CurrentMap->x;

                                if(ContainedRegions[CurrentRegion].FurthestRightPosition != -1)
                                {
                                    if(TempX1 > TempX2)
                                    {
                                        ContainedRegions[CurrentRegion].FurthestRightPosition = aRight;
                                    }
                                }
                                else if(ContainedRegions[CurrentRegion].FurthestRightPosition == -1)
                                {
                                    ContainedRegions[CurrentRegion].FurthestRightPosition = aRight;
                                }

                                if(DebugMessages)
                                {
                                    fout << "\nRight Added.";
                                }
                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\nAbove absolute value: " << aLeft;
                        fout << "\nAbove InWaterRegion: " << CurrentMap->data[aLeft].InWaterRegion;
                    }

                    if(aAbove > -1)
                    {
                        if(AboveHeight <= CurrentMap->SeaLevel)
                        {
                            if(CurrentMap->data[aAbove].InWaterRegion == 0)
                            {
                                CoordinateQueue.push(aAbove);
                                ContainedRegions[CurrentRegion].AddCoordinate(aAbove);
                                CurrentMap->data[aAbove].InWaterRegion = 1;

                                //int TempX1 = aAbove % CurrentMap->x;
                                int TempY1 = aAbove / CurrentMap->x;

                                //int TempX2 = ContainedRegions[CurrentRegion].FurthestUpPosition % CurrentMap->x;
                                int TempY2 = ContainedRegions[CurrentRegion].FurthestUpPosition / CurrentMap->x;

                                if(ContainedRegions[CurrentRegion].FurthestUpPosition != -1)
                                {
                                    if(TempY1 < TempY2)
                                    {
                                        ContainedRegions[CurrentRegion].FurthestUpPosition = aAbove;
                                    }
                                }
                                else if(ContainedRegions[CurrentRegion].FurthestUpPosition == -1)
                                {
                                    ContainedRegions[CurrentRegion].FurthestUpPosition = aAbove;
                                }

                                if(DebugMessages)
                                {
                                    fout << "\nAbove Added.";
                                }
                            }
                        }
                    }

                    if(DebugMessages)
                    {
                        fout << "\nBelow absolute value: " << aLeft;
                        fout << "\nBelow InWaterRegion: " << CurrentMap->data[aLeft].InWaterRegion;
                    }

                    if(aBelow > -1)
                    {
                        if(BelowHeight <= CurrentMap->SeaLevel)
                        {
                            if(CurrentMap->data[aBelow].InWaterRegion == 0)
                            {
                                CoordinateQueue.push(aBelow);
                                ContainedRegions[CurrentRegion].AddCoordinate(aBelow);
                                CurrentMap->data[aBelow].InWaterRegion = 1;

                                //int TempX1 = aBelow % CurrentMap->x;
                                int TempY1 = aBelow / CurrentMap->x;

                                //int TempX2 = ContainedRegions[CurrentRegion].FurthestDownPosition % CurrentMap->x;
                                int TempY2 = ContainedRegions[CurrentRegion].FurthestDownPosition / CurrentMap->x;

                                if(ContainedRegions[CurrentRegion].FurthestDownPosition != -1)
                                {
                                    if(TempY1 > TempY2)
                                    {
                                        ContainedRegions[CurrentRegion].FurthestDownPosition = aBelow;
                                    }

                                }
                                else if(ContainedRegions[CurrentRegion].FurthestDownPosition == -1)
                                {
                                    ContainedRegions[CurrentRegion].FurthestDownPosition = aBelow;
                                }

                                if(DebugMessages)
                                {
                                    fout << "\nBelow Added.";
                                }
                            }
                        }
                    }

                    CoordinateQueue.pop();
                }
                ContainedRegions[CurrentRegion].CalculateMidpoints();
                CurrentRegion++;
            }
        }


        if(GridX < XLimit && GridY == YLimit)
        {
            GridX++;
            GridY = 0;
        }
        else if(GridX <= XLimit && GridY < YLimit)
        {
            GridY++;
        }
        else if(GridX == XLimit && GridY == YLimit)
        {
            GridX++;
            GridY++;
        }
    }

    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";

    int RegionCount = (int)ContainedRegions.size();
    std::cout << "\n\nNumber of Regions: " << RegionCount;
}
