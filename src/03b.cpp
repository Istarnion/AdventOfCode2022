/***************************************************/
/*                                                 */
/*    File: 03b.cpp                                */
/* Created: 2022-12-03                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
As you finish identifying the misplaced items, the Elves come to you with another issue.

For safety, the Elves are divided into groups of three. Every Elf carries a badge that identifies their group. For efficiency, within each group of three Elves, the badge is the only item type carried by all three Elves. That is, if a group's badge is item type B, then all three Elves will have item type B somewhere in their rucksack, and at most two of the Elves will be carrying any other item type.

The problem is that someone forgot to put this year's updated authenticity sticker on the badges. All of the badges need to be pulled out of the rucksacks so the new authenticity stickers can be attached.

Additionally, nobody wrote down which item type corresponds to each group's badges. The only way to tell which item type is the right one is by finding the one item type that is common between all three Elves in each group.

Every set of three lines in your list corresponds to a single group, but each group can have a different badge item type. So, in the above example, the first group's rucksacks are the first three lines:

vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg

And the second group's rucksacks are the next three lines:

wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw

In the first group, the only item type that appears in all three rucksacks is lowercase r; this must be their badges. In the second group, their badge item type must be Z.

Priorities for these items must still be found to organize the sticker attachment efforts: here, they are 18 (r) for the first group and 52 (Z) for the second group. The sum of these is 70.

Find the item type that corresponds to the badges of each three-Elf group. What is the sum of the priorities of those item types?
*/

#include "common.h"
#include "03.h"

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("03.input", &LineCount);

    i32 Sum = 0;
    for(i32 I=0; I<LineCount; I+=3)
    {
        str *L1 = Lines + I;
        str *L2 = Lines + I + 1;
        str *L3 = Lines + I + 2;

        char Count[52] = { 0 };

        for(i32 I=0; I<L1->Length; ++I)
        {
            i32 Index = Priority(L1->Buffer[I]) - 1;
            Count[Index] |= 1;
        }

        for(i32 I=0; I<L2->Length; ++I)
        {
            i32 Index = Priority(L2->Buffer[I]) - 1;
            Count[Index] |= 2;
        }

        for(i32 I=0; I<L3->Length; ++I)
        {
            i32 Index = Priority(L3->Buffer[I]) - 1;
            Count[Index] |= 4;
        }

        for(i32 I=0; I<52; ++I)
        {
            if(Count[I] == 7)
            {
                Sum += (I + 1);
                break;
            }
        }
    }

    TimingEnd(&Timing);

    printf("The sum is %d\n", Sum);

    return 0;
}

