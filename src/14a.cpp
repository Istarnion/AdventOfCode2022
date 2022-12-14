/***************************************************/
/*                                                 */
/*    File: 14.cpp                                 */
/* Created: 2022-12-14                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
The distress signal leads you to a giant waterfall! Actually, hang on - the signal seems like it's coming from the waterfall itself, and that doesn't make any sense. However, you do notice a little path that leads behind the waterfall.

Correction: the distress signal leads you behind a giant waterfall! There seems to be a large cave system here, and the signal definitely leads further inside.

As you begin to make your way deeper underground, you feel the ground rumble for a moment. Sand begins pouring into the cave! If you don't quickly figure out where the sand is going, you could quickly become trapped!

Fortunately, your familiarity with analyzing the path of falling material will come in handy here. You scan a two-dimensional vertical slice of the cave above you (your puzzle input) and discover that it is mostly air with structures made of rock.

Your scan traces the path of each solid rock structure and reports the x,y coordinates that form the shape of the path, where x represents distance to the right and y represents distance down. Each path appears as a single line of text in your scan. After the first point of each path, each point indicates the end of a straight horizontal or vertical line to be drawn from the previous point. For example:

498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9

This scan means that there are two paths of rock; the first path consists of two straight lines, and the second path consists of three straight lines. (Specifically, the first path consists of a line of rock from 498,4 through 498,6 and another line of rock from 498,6 through 496,6.)

The sand is pouring into the cave from point 500,0.

Drawing rock as #, air as ., and the source of the sand as +, this becomes:


  4     5  5
  9     0  0
  4     0  3
0 ......+...
1 ..........
2 ..........
3 ..........
4 ....#...##
5 ....#...#.
6 ..###...#.
7 ........#.
8 ........#.
9 #########.

Sand is produced one unit at a time, and the next unit of sand is not produced until the previous unit of sand comes to rest. A unit of sand is large enough to fill one tile of air in your scan.

A unit of sand always falls down one step if possible. If the tile immediately below is blocked (by rock or sand), the unit of sand attempts to instead move diagonally one step down and to the left. If that tile is blocked, the unit of sand attempts to instead move diagonally one step down and to the right. Sand keeps moving as long as it is able to do so, at each step trying to move down, then down-left, then down-right. If all three possible destinations are blocked, the unit of sand comes to rest and no longer moves, at which point the next unit of sand is created back at the source.

So, drawing sand that has come to rest as o, the first unit of sand simply falls straight down and then stops:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
........#.
......o.#.
#########.

The second unit of sand then falls straight down, lands on the first one, and then comes to rest to its left:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
........#.
.....oo.#.
#########.

After a total of five units of sand have come to rest, they form this pattern:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
......o.#.
....oooo#.
#########.

After a total of 22 units of sand:

......+...
..........
......o...
.....ooo..
....#ooo##
....#ooo#.
..###ooo#.
....oooo#.
...ooooo#.
#########.

Finally, only two more units of sand can possibly come to rest:

......+...
..........
......o...
.....ooo..
....#ooo##
...o#ooo#.
..###ooo#.
....oooo#.
.o.ooooo#.
#########.

Once all 24 units of sand shown above have come to rest, all further sand flows out the bottom, falling into the endless void. Just for fun, the path any new sand takes before falling forever is shown here with ~:

.......+...
.......~...
......~o...
.....~ooo..
....~#ooo##
...~o#ooo#.
..~###ooo#.
..~..oooo#.
.~o.ooooo#.
~#########.
~..........
~..........
~..........

Using your scan, simulate the falling sand. How many units of sand come to rest before sand starts flowing into the abyss below?
*/

#include "common.h"

struct wall
{
    i32 PointCount;
    i32 X[32];
    i32 Y[32];
};

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("14.input", &LineCount);

    wall *Walls = (wall *)malloc(LineCount * sizeof(wall));

    i32 MinX = INT32_MAX;
    i32 MaxX = 0;
    i32 MaxY = 0;
    for(i32 I=0; I<LineCount; ++I)
    {
        Walls[I].PointCount = 0;
        while(true)
        {
            i32 X = ConsumeInt(Lines + I);
            Lines[I].Buffer++;
            Lines[I].Length--;
            i32 Y = ConsumeInt(Lines + I);

            if(X < MinX)
            {
                MinX = X;
            }

            if(X > MaxX)
            {
                MaxX = X;
            }

            if(Y > MaxY)
            {
                MaxY = Y;
            }

            Walls[I].X[Walls[I].PointCount] = X;
            Walls[I].Y[Walls[I].PointCount] = Y;
            Walls[I].PointCount++;

            if(Lines[I].Length == 0 || !StartsWith(Lines[I], " -> "))
            {
                break;
            }
            else
            {
                Consume(Lines + I, " -> ");
            }
        }
    }

    i32 Width = (MaxX+1) - MinX;
    i32 Height = MaxY+1;

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
                Map[(X-MinX) + Y * Width] = '#';
                X += DX;
                Y += DY;
            }

            Map[(X-MinX) + Y * Width] = '#';
        }
    }

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=0; X<Width; ++X)
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
        i32 X = 500 - MinX;
        i32 Y = 0;

        while(Running)
        {
            if(Y + 1 >= Height)
            {
                Running = false;
            }
            else if(Map[X + (Y+1) * Width] == '.')
            {
                Y++;
            }
            else if(X - 1 < 0)
            {
                Running = false;
            }
            else if(Map[(X-1) + (Y+1) * Width] == '.')
            {
                X--;
                Y++;
            }
            else if(X + 1 >= Width)
            {
                Running = false;
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
    }

    for(i32 Y=0; Y<Height; ++Y)
    {
        for(i32 X=0; X<Width; ++X)
        {
            putchar(Map[X + Y * Width]);
        }

        putchar('\n');
    }

    printf("%d units of sand settled\n", SettleCount);

    return 0;
}

