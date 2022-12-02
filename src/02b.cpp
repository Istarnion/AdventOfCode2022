/***************************************************/
/*                                                 */
/*    File: 02b.cpp                                */
/* Created: 2022-12-02                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
The Elf finishes helping with the tent and sneaks back over to you. "Anyway, the second column says how the round needs to end: X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win. Good luck!"

The total score is still calculated in the same way, but now you need to figure out what shape to choose so the round ends as indicated. The example above now goes like this:

    In the first round, your opponent will choose Rock (A), and you need the round to end in a draw (Y), so you also choose Rock. This gives you a score of 1 + 3 = 4.
    In the second round, your opponent will choose Paper (B), and you choose Rock so you lose (X) with a score of 1 + 0 = 1.
    In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = 7.

Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of 12.

Following the Elf's instructions for the second column, what would your total score be if everything goes exactly according to your strategy guide?
*/

#include "common.h"
#include "02.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("02.input", &LineCount);

    i32 Score = 0;
    for(i32 I=0; I<LineCount; ++I)
    {
        if(Lines[I].Length > 0)
        {
            char ElfCode = Lines[I].Buffer[0];
            char ResultCode = Lines[I].Buffer[2];

            rps ElfMove = ToRPS(ElfCode);
            result Result = ToResult(ResultCode);

            rps MyMove = ReverseRPS(Result, ElfMove);

            i32 Round = ((i32)MyMove) + 1;
            if(Result == DRAW)
            {
                Round += 3;
            }
            else if(Result == WIN)
            {
                Round += 6;
            }

            Score += Round;
        }
    }

    printf("The total score is %d\n", Score);

    return 0;
}

