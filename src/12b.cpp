/***************************************************/
/*                                                 */
/*    File: 12b.cpp                                */
/* Created: 2022-12-12                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
As you walk up the hill, you suspect that the Elves will want to turn this into a hiking trail. The beginning isn't very scenic, though; perhaps you can find a better starting point.

To maximize exercise while hiking, the trail should start as low as possible: elevation a. The goal is still the square marked E. However, the trail should still be direct, taking the fewest steps to reach its goal. So, you'll need to find the shortest path from any square at elevation a to the square marked E.

Again consider the example from above:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Now, there are six choices for starting position (five marked a, plus the square marked S that counts as being at elevation a). If you start at the bottom-left square, you can reach the goal most quickly:

...v<<<<
...vv<<^
...v>E^^
.>v>>>^^
>^>>>>>^

This path reaches the goal in only 29 steps, the fewest possible.

What is the fewest steps required to move starting from any square with elevation a to the location that should get the best signal?
*/

#include "common.h"
#include "12.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("12.input", &LineCount);

    i32 Width = Lines[0].Length;
    i32 Height = LineCount;

    cell *Map = (cell *)calloc(Width * Height, sizeof(cell));
    i32 StartX, StartY;

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=0; X<Width; ++X)
        {
            char C = Lines[Y].Buffer[X];
            if(C == 'S')
            {
                Map[X + Y * Width] =
                {
                    .Index = X + Y * Width,
                    .Dist = 0,
                    .Score = INT32_MAX,
                    .Height = 0,
                    .Closed = false
                };
            }
            else if(C == 'E')
            {
                StartX = X;
                StartY = Y;
                Map[X + Y * Width] =
                {
                    .Index = X + Y * Width,
                    .Dist = 0,
                    .Score = 0,
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

    i32 OpenListSize = 1;
    cell **OpenList = (cell **)calloc(1024, sizeof(cell));
    OpenList[0] = Map + (StartX + StartY * Width);

    while(OpenListSize)
    {
        cell *Current = Pop(&OpenListSize, OpenList);
        i32 X = Current->Index % Width;
        i32 Y = Current->Index / Width;

        if(Current->Height == 0)
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
            if(Neighbour && Current->Height - Neighbour->Height <= 1 && !Neighbour->Closed)
            {
                i32 PotentialScore = Current->Dist + 1;
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

    return 0;
}


