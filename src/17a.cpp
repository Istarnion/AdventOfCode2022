/***************************************************/
/*                                                 */
/*    File: 17a.cpp                                */
/* Created: 2022-12-17                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
Your handheld device has located an alternative exit from the cave for you and the elephants. The ground is rumbling almost continuously now, but the strange valves bought you some time. It's definitely getting warmer in here, though.

The tunnels eventually open into a very tall, narrow chamber. Large, oddly-shaped rocks are falling into the chamber from above, presumably due to all the rumbling. If you can't work out where the rocks will fall next, you might be crushed!

The five types of rocks have the following peculiar shapes, where # is rock and . is empty space:

####

.#.
###
.#.

..#
..#
###

#
#
#
#

##
##

The rocks fall in the order shown above: first the - shape, then the + shape, and so on. Once the end of the list is reached, the same order repeats: the - shape falls first, sixth, 11th, 16th, etc.

The rocks don't spin, but they do get pushed around by jets of hot gas coming out of the walls themselves. A quick scan reveals the effect the jets of hot gas will have on the rocks as they fall (your puzzle input).

For example, suppose this was the jet pattern in your cave:

>>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>

In jet patterns, < means a push to the left, while > means a push to the right. The pattern above means that the jets will push a falling rock right, then right, then right, then left, then left, then right, and so on. If the end of the list is reached, it repeats.

The tall, vertical chamber is exactly seven units wide. Each rock appears so that its left edge is two units away from the left wall and its bottom edge is three units above the highest rock in the room (or the floor, if there isn't one).

After a rock appears, it alternates between being pushed by a jet of hot gas one unit (in the direction indicated by the next symbol in the jet pattern) and then falling one unit down. If any movement would cause any part of the rock to move into the walls, floor, or a stopped rock, the movement instead does not occur. If a downward movement would have caused a falling rock to move into the floor or an already-fallen rock, the falling rock stops where it is (having landed on something) and a new rock immediately begins falling.

Drawing falling rocks with @ and stopped rocks with #, the jet pattern in the example above manifests as follows:

The first rock begins falling:
|..@@@@.|
|.......|
|.......|
|.......|
+-------+

Jet of gas pushes rock right:
|...@@@@|
|.......|
|.......|
|.......|
+-------+

Rock falls 1 unit:
|...@@@@|
|.......|
|.......|
+-------+

Jet of gas pushes rock right, but nothing happens:
|...@@@@|
|.......|
|.......|
+-------+

Rock falls 1 unit:
|...@@@@|
|.......|
+-------+

Jet of gas pushes rock right, but nothing happens:
|...@@@@|
|.......|
+-------+

Rock falls 1 unit:
|...@@@@|
+-------+

Jet of gas pushes rock left:
|..@@@@.|
+-------+

Rock falls 1 unit, causing it to come to rest:
|..####.|
+-------+

A new rock begins falling:
|...@...|
|..@@@..|
|...@...|
|.......|
|.......|
|.......|
|..####.|
+-------+

Jet of gas pushes rock left:
|..@....|
|.@@@...|
|..@....|
|.......|
|.......|
|.......|
|..####.|
+-------+

Rock falls 1 unit:
|..@....|
|.@@@...|
|..@....|
|.......|
|.......|
|..####.|
+-------+

Jet of gas pushes rock right:
|...@...|
|..@@@..|
|...@...|
|.......|
|.......|
|..####.|
+-------+

Rock falls 1 unit:
|...@...|
|..@@@..|
|...@...|
|.......|
|..####.|
+-------+

Jet of gas pushes rock left:
|..@....|
|.@@@...|
|..@....|
|.......|
|..####.|
+-------+

Rock falls 1 unit:
|..@....|
|.@@@...|
|..@....|
|..####.|
+-------+

Jet of gas pushes rock right:
|...@...|
|..@@@..|
|...@...|
|..####.|
+-------+

Rock falls 1 unit, causing it to come to rest:
|...#...|
|..###..|
|...#...|
|..####.|
+-------+

A new rock begins falling:
|....@..|
|....@..|
|..@@@..|
|.......|
|.......|
|.......|
|...#...|
|..###..|
|...#...|
|..####.|
+-------+

The moment each of the next few rocks begins falling, you would see this:

|..@....|
|..@....|
|..@....|
|..@....|
|.......|
|.......|
|.......|
|..#....|
|..#....|
|####...|
|..###..|
|...#...|
|..####.|
+-------+

|..@@...|
|..@@...|
|.......|
|.......|
|.......|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|..@@@@.|
|.......|
|.......|
|.......|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|...@...|
|..@@@..|
|...@...|
|.......|
|.......|
|.......|
|.####..|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|....@..|
|....@..|
|..@@@..|
|.......|
|.......|
|.......|
|..#....|
|.###...|
|..#....|
|.####..|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|..@....|
|..@....|
|..@....|
|..@....|
|.......|
|.......|
|.......|
|.....#.|
|.....#.|
|..####.|
|.###...|
|..#....|
|.####..|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|..@@...|
|..@@...|
|.......|
|.......|
|.......|
|....#..|
|....#..|
|....##.|
|....##.|
|..####.|
|.###...|
|..#....|
|.####..|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

|..@@@@.|
|.......|
|.......|
|.......|
|....#..|
|....#..|
|....##.|
|##..##.|
|######.|
|.###...|
|..#....|
|.####..|
|....##.|
|....##.|
|....#..|
|..#.#..|
|..#.#..|
|#####..|
|..###..|
|...#...|
|..####.|
+-------+

To prove to the elephants your simulation is accurate, they want to know how tall the tower will get after 2022 rocks have stopped (but before the 2023rd rock begins falling). In this example, the tower of rocks will be 3068 units tall.

How many units tall will the tower of rocks be after 2022 rocks have stopped falling?
*/

#include "common.h"

struct rock
{
    i32 Height;
    u8 Shape[4];
};

constexpr rock Rocks[5] =
{
    {   // -
        .Height = 1,
        .Shape =
        {
             0,
             0,
             0,
            60  // 00111100
        }
    },
    {   // +
        .Height = 3,
        .Shape =
        {
             0,
            16, // 00010000
            56, // 00111000
            16  // 00010000
        }
    },
    {   // j
        .Height = 3,
        .Shape =
        {
             0,
             8, // 00001000
             8, // 00001000
            56  // 00111000
        }
    },
    {   // |
        .Height = 4,
        .Shape =
        {
            32, // 00100000
            32, // 00100000
            32, // 00100000
            32  // 00100000
        }
    },
    {   // #
        .Height = 2,
        .Shape =
        {
             0,
             0,
            48, // 00110000
            48  // 00110000
        }
    }
};

static inline bool
CanMoveLeft(const rock &Rock)
{
    bool Result = true;
    for(i32 I=0; I<4; ++I)
    {
        if(Rock.Shape[I] & 128)
        {
            Result = false;
            break;
        }
    }

    return Result;
}

static inline bool
CanMoveRight(const rock &Rock)
{
    bool Result = true;
    for(i32 I=0; I<4; ++I)
    {
        if(Rock.Shape[I] & 3)
        {
            Result = false;
            break;
        }
    }

    return Result;
}

static inline void
PrintRock(rock Rock)
{
    for(i32 I=0; I<4; ++I)
    {
        u8 Line = Rock.Shape[I];
        for(i32 X=0; X<7; ++X)
        {
            putchar((Line & 128) ? '#' : '.');
            Line = Line << 1;
        }
        putchar('\n');
    }
}

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);
    str Gusts = ReadEntireFile("17.input");
    TimingPostParsing(&Timing);

    constexpr i32 RoundCount = 2022;

    i32 Piece = 0;
    i32 GustIndex = 0;
    constexpr i32 MaxHeight = 4*RoundCount;
    u8 *Chamber = (u8 *)calloc(MaxHeight, 1);

    i32 Height = 0;

    for(i32 Round = 0; Round<RoundCount; ++Round)
    {
        if(Piece >= 5) Piece = 0;
        rock Rock = Rocks[Piece++];

        i32 Y = Height + 3;
        i32 PotentialHeight = 3 + Rock.Height;

        bool Falling = true;
        while(Falling)
        {
            // Handle gust
            if(GustIndex >= Gusts.Length) GustIndex = 0;
            char Gust = Gusts.Buffer[GustIndex++];
            Assert(Gust == '<' || Gust == '>', "Invalid gust");

            rock New = Rock;

            if(Gust == '<' && CanMoveLeft(New))
            {
                for(i32 I=0; I<4; ++I)
                {
                    New.Shape[I] = New.Shape[I] << 1;
                }
            }
            else if(Gust == '>' && CanMoveRight(New))
            {
                for(i32 I=0; I<4; ++I)
                {
                    New.Shape[I] = New.Shape[I] >> 1;
                }
            }

            for(i32 I=0; I<4; ++I)
            {
                if(Chamber[Y+(3-I)] & New.Shape[I])
                {
                    // Collision, cannot move horizontally
                    New = Rock; // Revert the above
                }
            }

            // putchar(Gust);

            Rock = New;

            // Move down
            for(i32 I=0; I<4; ++I)
            {
                if(Y <= 0 || Chamber[Y+(3-I)-1] & Rock.Shape[I])
                {
                    Falling = false;
                }
            }

            if(Falling)
            {
                PotentialHeight--;
                Y--;
            }
        }

        for(i32 I=0; I<4; ++I)
        {
            Chamber[Y+(3-I)] |= Rock.Shape[I];
        }

        if(PotentialHeight > 0)
        {
            Height += PotentialHeight;
        }

    }

    /*
    for(i32 Y=Height; Y-->0;)
    {
        u8 Line = Chamber[Y];
        putchar('|');
        for(i32 X=0; X<7; ++X)
        {
            putchar((Line & 128) ? '#' : '.');
            Line = Line << 1;
        }
        puts("|");
    }

    puts("+-------+");
    */

    TimingEnd(&Timing);

    printf("Final height of tower is %d\n", Height);

    return 0;
}

