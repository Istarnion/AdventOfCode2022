/***************************************************/
/*                                                 */
/*    File: 14b.cpp                                */
/* Created: 2022-12-14                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
You realize you misread the scan. There isn't an endless void at the bottom of the scan - there's floor, and you're standing on it!

You don't have time to scan the floor, so assume the floor is an infinite horizontal line with a y coordinate equal to two plus the highest y coordinate of any point in your scan.

In the example above, the highest y coordinate of any point is 9, and so the floor is at y=11. (This is as if your scan contained one extra rock path like -infinity,11 -> infinity,11.) With the added floor, the example above now looks like this:

        ...........+........
        ....................
        ....................
        ....................
        .........#...##.....
        .........#...#......
        .......###...#......
        .............#......
        .............#......
        .....#########......
        ....................
<-- etc #################### etc -->

To find somewhere safe to stand, you'll need to simulate falling sand until a unit of sand comes to rest at 500,0, blocking the source entirely and stopping the flow of sand into the cave. In the example above, the situation finally looks like this after 93 units of sand come to rest:

............o............
...........ooo...........
..........ooooo..........
.........ooooooo.........
........oo#ooo##o........
.......ooo#ooo#ooo.......
......oo###ooo#oooo......
.....oooo.oooo#ooooo.....
....oooooooooo#oooooo....
...ooo#########ooooooo...
..ooooo.......ooooooooo..
#########################

Using your scan, simulate the falling sand until the source of the sand becomes blocked. How many units of sand come to rest?
*/

#include "common.h"
#include "14.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("14.input", &LineCount);

    i32 MinX, MaxX, MaxY;
    wall *Walls = ParseWalls(LineCount, Lines, &MinX, &MaxX, &MaxY);

    i32 Width = ((MaxX+1) - MinX) * 9;
    i32 Height = MaxY+2;
    i32 XOffset = -MinX + 4*((MaxX+1) - MinX);

    char *Map = (char *)malloc(Width * Height);
    memset(Map, '.', Width * Height);

    for(i32 I=0; I<LineCount; ++I)
    {
        i32 X = Walls[I].X[0];
        i32 Y = Walls[I].Y[0];
        for(i32 J=1; J<Walls[I].PointCount; ++J)
        {
            i32 DX = Sign(Walls[I].X[J] - X);
            i32 DY = Sign(Walls[I].Y[J] - Y);

            while(X != Walls[I].X[J] || Y != Walls[I].Y[J])
            {
                Map[(X+XOffset) + Y * Width] = '#';
                X += DX;
                Y += DY;
            }

            Map[(X+XOffset) + Y * Width] = '#';
        }
    }

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=4*((MaxX+1) - MinX); X<(Width-4*((MaxX+1) - MinX)); ++X)
        {
            putchar(Map[X + Y * Width]);
        }

        putchar('\n');
    }

    putchar('\n');

    i32 SettleCount = 0;
    i32 Running = true;
    while(Running)
    {
        i32 X = 500 + XOffset;
        i32 Y = 0;

        while(Running)
        {
            if(Y + 1 >= Height)
            {
                SettleCount++;
                Map[X + Y * Width] = 'o';
                break;
            }
            else if(Map[X + (Y+1) * Width] == '.')
            {
                Y++;
            }
            else if(X - 1 < 0)
            {
                Assert(false, "Overflowing left");
            }
            else if(Map[(X-1) + (Y+1) * Width] == '.')
            {
                X--;
                Y++;
            }
            else if(X + 1 >= Width)
            {
                Assert(false, "Overflowing right");
            }
            else if(Map[(X+1) + (Y+1) * Width] == '.')
            {
                X++;
                Y++;
            }
            else
            {
                SettleCount++;
                Map[X + Y * Width] = 'o';
                break;
            }
        }

        Running = !(X == 500 + XOffset && Y == 0);
    }

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=4*((MaxX+1) - MinX); X<(Width-4*((MaxX+1) - MinX)); ++X)
        {
            putchar(Map[X + Y * Width]);
        }

        putchar('\n');
    }

    printf("%d units of sand settled\n", SettleCount);

    return 0;
}

