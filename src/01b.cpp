/***************************************************/
/*                                                 */
/*    File: 01b.cpp                                */
/* Created: 2022-12-02                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories of food might eventually run out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three Elves carrying the most Calories. That way, even if one of those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with 10000 Calories). The sum of the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?
*/

#include "common.h"

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);
    i32 LineCount;
    str *Lines = ReadLinesFromFile("01.input", &LineCount);

    i32 MaxCalories[3] = { 0, 0, 0 };

    i32 Calories = 0;
    for(i32 I=0; I<LineCount; ++I)
    {
        if(Lines[I].Length > 0)
        {
            Calories += ToInt(Lines[I]);
        }
        else
        {
            for(i32 J=0; J<3; ++J)
            {
                if(Calories > MaxCalories[J])
                {
                    for(i32 K=J; K<3; ++K)
                    {
                        i32 Temp = MaxCalories[K];
                        MaxCalories[K] = Calories;
                        Calories = Temp;
                    }

                    break;
                }
            }

            Calories = 0;
        }
    }

    i32 Sum = MaxCalories[0] + MaxCalories[1] + MaxCalories[2];

    TimingEnd(&Timing);

    printf("The top 3 elves carry a combined %d calories\n", Sum);

    return 0;
}

