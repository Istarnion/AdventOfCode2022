/***************************************************/
/*                                                 */
/*    File: 08a.cpp                                */
/* Created: 2022-12-08                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
The expedition comes across a peculiar patch of tall trees all planted carefully in a grid. The Elves explain that a previous expedition planted these trees as a reforestation effort. Now, they're curious if this would be a good location for a tree house.

First, determine whether there is enough tree cover here to keep a tree house hidden. To do this, you need to count the number of trees that are visible from outside the grid when looking directly along a row or column.

The Elves have already launched a quadcopter to generate a map with the height of each tree (your puzzle input). For example:

30373
25512
65332
33549
35390

Each tree is represented as a single digit whose value is its height, where 0 is the shortest and 9 is the tallest.

A tree is visible if all of the other trees between it and an edge of the grid are shorter than it. Only consider trees in the same row or column; that is, only look up, down, left, or right from any given tree.

All of the trees around the edge of the grid are visible - since they are already on the edge, there are no trees to block the view. In this example, that only leaves the interior nine trees to consider:

    The top-left 5 is visible from the left and top. (It isn't visible from the right or bottom since other trees of height 5 are in the way.)
    The top-middle 5 is visible from the top and right.
    The top-right 1 is not visible from any direction; for it to be visible, there would need to only be trees of height 0 between it and an edge.
    The left-middle 5 is visible, but only from the right.
    The center 3 is not visible from any direction; for it to be visible, there would need to be only trees of at most height 2 between it and an edge.
    The right-middle 3 is visible from the right.
    In the bottom row, the middle 5 is visible, but the 3 and 4 are not.

With 16 trees visible on the edge and another 5 visible in the interior, a total of 21 trees are visible in this arrangement.

Consider your map; how many trees are visible from outside the grid?
 */

#include "common.h"
#include "08.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 Height;
    str *Lines = ReadLinesFromFile("08.input", &Height);
    i32 Width = Lines[0].Length;

    i32 Sum = 0;
    for(i32 Row=0; Row<Height; ++Row)
    {
        for(i32 Col=0; Col<Width; ++Col)
        {
            i32 H = At(Col, Row, Lines, Width, Height);
            i32 Visible = 4;

            for(i32 X=Col-1; X>=0; --X)
            {
                if(H <= At(X, Row, Lines, Width, Height))
                {
                    Visible--;
                    break;
                }
            }

            for(i32 X=Col+1; X<Width; ++X)
            {
                if(H <= At(X, Row, Lines, Width, Height))
                {
                    Visible--;
                    break;
                }
            }

            for(i32 Y=Row-1; Y>=0; --Y)
            {
                if(H <= At(Col, Y, Lines, Width, Height))
                {
                    Visible--;
                    break;
                }
            }

            for(i32 Y=Row+1; Y<Height; ++Y)
            {
                if(H <= At(Col, Y, Lines, Width, Height))
                {
                    Visible--;
                    break;
                }
            }

            Sum += !!(Visible > 0);
        }
    }

    printf("The number of visible trees is %d\n", Sum);

    return 0;
}

