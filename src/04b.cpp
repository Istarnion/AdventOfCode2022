/***************************************************/
/*                                                 */
/*    File: 04a.cpp                                */
/* Created: 2022-12-04                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
It seems like there is still quite a bit of duplicate work planned. Instead, the Elves would like to know the number of pairs that overlap at all.

In the above example, the first two pairs (2-4,6-8 and 2-3,4-5) don't overlap, while the remaining four pairs (5-7,7-9, 2-8,3-7, 6-6,4-6, and 2-6,4-8) do overlap:

    5-7,7-9 overlaps in a single section, 7.
    2-8,3-7 overlaps all of the sections 3 through 7.
    6-6,4-6 overlaps in a single section, 6.
    2-6,4-8 overlaps in sections 4, 5, and 6.

So, in this example, the number of overlapping assignment pairs is 4.

In how many assignment pairs do the ranges overlap?
*/

#include "common.h"
#include "04.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("04.input", &LineCount);

    i32 Count = 0;
    for(i32 I=0; I<LineCount; ++I)
    {
        i32 MinA, MaxA, MinB, MaxB;
        ParsePairs(Lines[I], &MinA, &MaxA, &MinB, &MaxB);

        Count += !(MaxA < MinB || MinA > MaxB);
    }

    printf("The number of overlapping pairs is %d\n", Count);

    return 0;
}

