/***************************************************/
/*                                                 */
/*    File: 06b.cpp                                */
/* Created: 2022-12-06                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
Your device's communication system is correctly detecting packets, but still isn't working. It looks like it also needs to look for messages.

A start-of-message marker is just like a start-of-packet marker, except it consists of 14 distinct characters rather than 4.

Here are the first positions of start-of-message markers for all of the above examples:

    mjqjpqmgbljsphdztnvjfqwrcgsmlb: first marker after character 19
    bvwbjplbgvbhsrlpgdmjqwftvncz: first marker after character 23
    nppdvjthqldpwncqszvftbrmjlhg: first marker after character 23
    nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg: first marker after character 29
    zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw: first marker after character 26

How many characters need to be processed before the first start-of-message marker is detected?
*/

#include "common.h"

static inline bool
AllUnique(char *Start, i32 N)
{
    char Count[256] = { 0 };
    i32 Min = 256;
    i32 Max = 0;
    for(i32 I=0; I<N; ++I)
    {
        i32 C = (i32)Start[I];
        if(C < Min) Min = C;
        if(C > Max) Max = C;
        Count[C]++;
    }

    bool Result = true;
    for(i32 I=Min; I<=Max; ++I)
    {
        if(Count[I] > 1)
        {
            Result = false;
            break;
        }
    }

    return Result;
}

int
main(i32 NumArgs, char *Args[])
{
    str Input = ReadEntireFile("06.input");

    i32 Count = 0;
    for(i32 I=13; I<Input.Length; ++I)
    {
        if(AllUnique(Input.Buffer + (I-13), 14))
        {
            Count = I+1;
            break;
        }
    }

    printf("%d characters needs to be processed before the start-of-packet is detected\n", Count);

    return 0;
}

