#include "GameMap.h"

void MapSystem::HeightRegionManager::CreateHeightBounds(int NumOfTiers)
{
    int TierSize = 256 / NumOfTiers;
    NumberOfTiers = NumOfTiers;

    for(int i = 0; i <= NumOfTiers; i++)
    {
        HeightTierContainer.push_back(MapSystem::HeightRegionInfo());
        HeightTierContainer[i].TierNumber = i;
        HeightTierContainer[i].TierSize = TierSize;
        if(i == 0)
        {
            HeightTierContainer[i].MinValue = 0;
            HeightTierContainer[i].MaxValue = TierSize - 1;
        }
        else if(i != 0)
        {
            HeightTierContainer[i].MaxValue = (i * TierSize) - 1;
            HeightTierContainer[i].MinValue = (HeightTierContainer[i].MaxValue - TierSize);
        }
    }
}

bool MapSystem::HeightRegionManager::WithinTierBounds(int CurrentTier, int Value)
{
    if(Value >= HeightTierContainer[CurrentTier].MinValue && Value <= HeightTierContainer[CurrentTier].MaxValue)
    {
        return 1;
    }
    return 0;
}

bool MapSystem::HeightRegionManager::Contained(int Position)
{
    for(std::vector <MapSystem::HeightRegion>::iterator CurrentVectorPos = HeightRegionContainer.begin(); CurrentVectorPos!= HeightRegionContainer.end(); CurrentVectorPos++ )
    {
        if((*CurrentVectorPos).Contains(Position))
        {
            return 1;
        }
    }

    return 0;
}

void MapSystem::HeightRegionManager::CalculateHeightRegions(bool DebugMessages)
{
    char FileName[] = "";//C:/Users/moneyl/Desktop/HeightRegionDetection.txt";
    std::ofstream fout(FileName, std::ios::trunc);

    if(DebugMessages)
    {
        fout << "~~~BEGINNING_OF_ENTRY~~~";
    }

    std::cout << "\n\nStarting Height Region Detection...   ";
    sf::Clock FunctionTime;
    FunctionTime.restart();

    int GridX = 0;
    int GridY = 0;

    int XLimit = CurrentMap->x - 1;
    int YLimit = CurrentMap->y - 1;

    std::queue <int> CoordinateQueue;

    int CurrentRegion = 0;

    for(int i = 0; i <= NumberOfTiers - 1; i++)
    {
        //i = Current Height Tier

        GridX = 0;
        GridY = 0;

        while(GridX <= XLimit && GridY <= YLimit)
        {
            int TempArrayPos = CurrentMap->ConvertToAbsolute(GridX, GridY);

            if(WithinTierBounds(i, CurrentMap->data[TempArrayPos].z) == 1)
            {
                if(DebugMessages)
                {
                    fout << "\n\nCurrentTier: " << i;
                    fout << "\nWITHIN CURRENT TIER BOUNDS LOOP_ONE: " << "X: " << GridX << " Y: " << GridY;
                    //fout << "\nTempArrayPos: " << TempArrayPos;
                }

                if(CurrentMap->data[TempArrayPos].InHeightRegion == 0)
                {
                    CoordinateQueue.push(TempArrayPos);
                    HeightRegionContainer.push_back(MapSystem::HeightRegion());

                    HeightRegionContainer[CurrentRegion].HeightRegionNumber = CurrentRegion;
                    HeightRegionContainer[CurrentRegion].TierNumber = i;
                    HeightRegionContainer[CurrentRegion].TierMin = HeightTierContainer[i].MinValue;
                    HeightRegionContainer[CurrentRegion].TierMax = HeightTierContainer[i].MaxValue;
                    HeightRegionContainer[CurrentRegion].CurrentMap = CurrentMap;

                    while(CoordinateQueue.empty() == 0)
                    {
                        if(DebugMessages)
                        {
                            fout << "\nQueue not empty.";
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
                        int aUpperLeft = CurrentMap->data[CoordinatePos].UpperLeft();
                        int aUpperRight = CurrentMap->data[CoordinatePos].UpperRight();
                        int aLowerLeft = CurrentMap->data[CoordinatePos].LowerLeft();
                        int aLowerRight = CurrentMap->data[CoordinatePos].LowerRight();

                        if(DebugMessages)
                        {
                            fout << "\nLeft absolute value: " << aLeft;
                            fout << "\nLeft InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aLeft > -1)
                        {
                            if(CurrentMap->data[aLeft].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aLeft].z))
                                {
                                    CoordinateQueue.push(aLeft);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aLeft);
                                    CurrentMap->data[aLeft].InHeightRegion = 1;
                                    CurrentMap->data[aLeft].HeightTier = i;
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
                            fout << "\nRight InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aRight > -1)
                        {
                            if(CurrentMap->data[aRight].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aRight].z))
                                {
                                    CoordinateQueue.push(aRight);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aRight);
                                    CurrentMap->data[aRight].InHeightRegion = 1;
                                    CurrentMap->data[aRight].HeightTier = i;
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
                            fout << "\nAbove InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aAbove > -1)
                        {
                            if(CurrentMap->data[aAbove].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aAbove].z))
                                {
                                    CoordinateQueue.push(aAbove);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aAbove);
                                    CurrentMap->data[aAbove].InHeightRegion = 1;
                                    CurrentMap->data[aAbove].HeightTier = i;
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
                            fout << "\nBelow InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aBelow > -1)
                        {
                            if(CurrentMap->data[aBelow].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aBelow].z))
                                {
                                    CoordinateQueue.push(aBelow);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aBelow);
                                    CurrentMap->data[aBelow].InHeightRegion = 1;
                                    CurrentMap->data[aBelow].HeightTier = i;
                                    if(DebugMessages)
                                    {
                                        fout << "\nBelow Added.";
                                    }
                                }
                            }
                        }

                        if(DebugMessages)
                        {
                            fout << "\nUpperLeft absolute value: " << aLeft;
                            fout << "\nUpperLeft InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aUpperLeft > -1)
                        {
                            if(CurrentMap->data[aUpperLeft].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aUpperLeft].z))
                                {
                                    CoordinateQueue.push(aUpperLeft);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aUpperLeft);
                                    CurrentMap->data[aUpperLeft].InHeightRegion = 1;
                                    CurrentMap->data[aUpperLeft].HeightTier = i;
                                    if(DebugMessages)
                                    {
                                        fout << "\nUpperLeft Added.";
                                    }
                                }
                            }
                        }

                        if(DebugMessages)
                        {
                            fout << "\nUpperRight absolute value: " << aLeft;
                            fout << "\nUpperRight InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aUpperRight > -1)
                        {
                            if(CurrentMap->data[aUpperRight].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aUpperRight].z))
                                {
                                    CoordinateQueue.push(aUpperRight);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aUpperRight);
                                    CurrentMap->data[aUpperRight].InHeightRegion = 1;
                                    CurrentMap->data[aUpperRight].HeightTier = i;
                                    if(DebugMessages)
                                    {
                                        fout << "\nUpperRight Added.";
                                    }
                                }
                            }
                        }

                        if(DebugMessages)
                        {
                            fout << "\nLowerLeft absolute value: " << aLeft;
                            fout << "\nLowerLeft InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aLowerLeft > -1)
                        {
                            if(CurrentMap->data[aLowerLeft].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aLowerLeft].z))
                                {
                                    CoordinateQueue.push(aLowerLeft);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aLowerLeft);
                                    CurrentMap->data[aLowerLeft].InHeightRegion = 1;
                                    CurrentMap->data[aLowerLeft].HeightTier = i;
                                    if(DebugMessages)
                                    {
                                        fout << "\nLowerLeft Added.";
                                    }
                                }
                            }
                        }

                        if(DebugMessages)
                        {
                            fout << "\nLowerRight absolute value: " << aLeft;
                            fout << "\nLowerRight InBiomeRegion: " << CurrentMap->data[aLeft].InBiomeRegion;
                        }

                        if(aLowerRight > -1)
                        {
                            if(CurrentMap->data[aLowerRight].InHeightRegion == 0)
                            {
                                if(WithinTierBounds(i, CurrentMap->data[aLowerRight].z))
                                {
                                    CoordinateQueue.push(aLowerRight);
                                    HeightRegionContainer[CurrentRegion].AddCoordinate(aLowerRight);
                                    CurrentMap->data[aLowerRight].InHeightRegion = 1;
                                    CurrentMap->data[aLowerRight].HeightTier = i;
                                    if(DebugMessages)
                                    {
                                        fout << "\nLowerRight Added.";
                                    }
                                }
                            }
                        }
                        CoordinateQueue.pop();
                    }
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
    }
    sf::Time FunctionSeconds = FunctionTime.getElapsedTime();
    std::cout <<  FunctionSeconds.asSeconds() << " Seconds.";

    int RegionCount = (int)HeightRegionContainer.size();
    std::cout << "\n\nNumber of Regions: " << RegionCount;
}

void MapSystem::HeightRegionManager::Reset()
{
    while(HeightTierContainer.empty() == 0)
    {
        HeightTierContainer.pop_back();
    }
    while(HeightRegionContainer.empty() == 0)
    {
        HeightRegionContainer.pop_back();
    }
}
