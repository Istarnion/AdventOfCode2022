/***************************************************/
/*                                                 */
/*    File: 12a.cpp                                */
/* Created: 2022-12-12                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
You try contacting the Elves using your handheld device, but the river you're following must be too low to get a decent signal.

You ask the device for a heightmap of the surrounding area (your puzzle input). The heightmap shows the local area from above broken into a grid; the elevation of each square of the grid is given by a single lowercase letter, where a is the lowest elevation, b is the next-lowest, and so on up to the highest elevation, z.

Also included on the heightmap are marks for your current position (S) and the location that should get the best signal (E). Your current position (S) has elevation a, and the location that should get the best signal (E) has elevation z.

You'd like to reach E, but to save energy, you should do it in as few steps as possible. During each step, you can move exactly one square up, down, left, or right. To avoid needing to get out your climbing gear, the elevation of the destination square can be at most one higher than the elevation of your current square; that is, if your current elevation is m, you could step to elevation n, but not to elevation o. (This also means that the elevation of the destination square can be much lower than the elevation of your current square.)

For example:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Here, you start in the top-left corner; your goal is near the middle. You could start by moving down or right, but eventually you'll need to head toward the e at the bottom. From there, you can spiral around to the goal:

v..v<<<<
>v.vv<<^
.>vv>E^^
..v>>>^^
..>>>>>^

In the above diagram, the symbols indicate whether the path exits each square moving up (^), down (v), left (<), or right (>). The location that should get the best signal is still E, and . marks unvisited squares.

This path reaches the goal in 31 steps, the fewest possible.

What is the fewest steps required to move from your current position to the location that should get the best signal?
*/

#include "common.h"
#include "12.h"

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("12.input", &LineCount);

    i32 Width = Lines[0].Length;
    i32 Height = LineCount;

    cell *Map = (cell *)calloc(Width * Height, sizeof(cell));
    i32 StartX, StartY;
    i32 EndX, EndY;

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=0; X<Width; ++X)
        {
            char C = Lines[Y].Buffer[X];
            if(C == 'S')
            {
                StartX = X;
                StartY = Y;
                Map[X + Y * Width] =
                {
                    .Index = X + Y * Width,
                    .Dist = 0,
                    .Score = 0,
                    .Height = 0,
                    .Closed = false
                };
            }
            else if(C == 'E')
            {
                EndX = X;
                EndY = Y;
                Map[X + Y * Width] =
                {
                    .Index = X + Y * Width,
                    .Dist = 0,
                    .Score = INT32_MAX,
                    .Height = 'z' - 'a',
                    .Closed = false
                };
            }
            else
            {
                Map[X + Y * Width] =
                {
                    .Index = X + Y * Width,
                    .Dist = 0,
                    .Score = INT32_MAX,
                    .Height = C - 'a',
                    .Closed = false
                };
            }
        }
    }

    TimingPostParsing(&Timing);

    i32 OpenListSize = 1;
    cell **OpenList = (cell **)calloc(1024, sizeof(cell));
    OpenList[0] = Map + (StartX + StartY * Width);

    while(OpenListSize)
    {
        cell *Current = Pop(&OpenListSize, OpenList);
        i32 X = Current->Index % Width;
        i32 Y = Current->Index / Width;

        if(X == EndX && Y == EndY)
        {
            printf("Path found! Length: %d\n", Current->Score);
            break;
        }

        cell *Neighbours[4] = { 0 };
        if(X > 0)
        {
            Neighbours[0] = Map + ((X-1) + Y * Width);
        }

        if(X < Width-1)
        {
            Neighbours[1] = Map + ((X+1) + Y * Width);
        }

        if(Y > 0)
        {
            Neighbours[2] = Map + (X + (Y-1) * Width);
        }

        if(Y < Height-1)
        {
            Neighbours[3] = Map + (X + (Y+1) * Width);
        }

        for(i32 I=0; I<4; ++I)
        {
            cell *Neighbour = Neighbours[I];
            if(Neighbour && Neighbour->Height - Current->Height <= 1 && !Neighbour->Closed)
            {
                i32 NX = Neighbour->Index % Width;
                i32 NY = Neighbour->Index / Width;
                i32 Heuristic = abs(EndX - NX) + abs(EndY - NY);

                i32 PotentialScore = Current->Dist + 1 + Heuristic;
                if(PotentialScore < Neighbour->Score)
                {
                    Neighbour->Score = PotentialScore;
                    Neighbour->Dist = Current->Dist + 1;

                    i32 J;
                    for(J=0; J<OpenListSize; ++J)
                    {
                        if(OpenList[J] == Neighbour)
                        {
                            break;
                        }
                    }

                    if(J == OpenListSize) // Neighbour not in open list, add it
                    {
                        OpenList[OpenListSize++] = Neighbour;
                        Assert(OpenListSize < 1024, "OpenList overflow");
                    }

                    HeapifyUp(OpenListSize, OpenList, J);
                }
            }
        }

        Current->Closed = true;
    }

    TimingEnd(&Timing);

    return 0;
}

