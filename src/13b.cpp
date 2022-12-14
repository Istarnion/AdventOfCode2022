/***************************************************/
/*                                                 */
/*    File: 13b.cpp                                */
/* Created: 2022-12-13                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
Now, you just need to put all of the packets in the right order. Disregard the blank lines in your list of received packets.

The distress signal protocol also requires that you include two additional divider packets:

[[2]]
[[6]]

Using the same rules as before, organize all packets - the ones in your list of received packets as well as the two divider packets - into the correct order.

For the example above, the result of putting the packets in the correct order is:

[]
[[]]
[[[]]]
[1,1,3,1,1]
[1,1,5,1,1]
[[1],[2,3,4]]
[1,[2,[3,[4,[5,6,0]]]],8,9]
[1,[2,[3,[4,[5,6,7]]]],8,9]
[[1],4]
[[2]]
[3]
[[4,4],4,4]
[[4,4],4,4,4]
[[6]]
[7,7,7]
[7,7,7,7]
[[8,7,6]]
[9]

Afterward, locate the divider packets. To find the decoder key for this distress signal, you need to determine the indices of the two divider packets and multiply them together. (The first packet is at index 1, the second packet is at index 2, and so on.) In this example, the divider packets are 10th and 14th, and so the decoder key is 140.

Organize all of the packets into the correct order. What is the decoder key for the distress signal?
*/

#include "common.h"
#include "13.h"

struct pool
{
    value *Pool;
    u32 PoolSize;
};

static int
SortCompare(void *Userdata, const void *L, const void *R)
{
    pool *Pool = (pool *)Userdata;
    str *Left = (str *)L;
    str *Right = (str *)R;

    value *A = ParseLine(*Left, &Pool->PoolSize, Pool->Pool);
    value *B = ParseLine(*Right, &Pool->PoolSize, Pool->Pool);
    Pool->PoolSize = 0;

    return Compare(A, B, &Pool->PoolSize, Pool->Pool);
}

static void
Sort(i32 Count, str *List, pool *Pool)
{
    qsort_r(List, Count, sizeof(str), Pool, SortCompare);
}

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("13.input", &LineCount);

    pool Pool;
    Pool.Pool = (value *)calloc(PoolCapacity, sizeof(value));
    Assert(Pool.Pool, "Failed to allocate pool");
    Pool.PoolSize = 0;

    str Signals[512];
    i32 SignalCount = 0;

    char TokenAStr[6] = "[[2]]";
    str TokenA = { .Buffer = TokenAStr, .Length = 5 };
    Signals[SignalCount++] = TokenA;

    char TokenBStr[6] = "[[6]]";
    str TokenB = { .Buffer = TokenBStr, .Length = 5 };
    Signals[SignalCount++] = TokenB;

    for(i32 I=0; I<LineCount; I+=3)
    {
        Signals[SignalCount++] = Lines[I];
        Signals[SignalCount++] = Lines[I+1];
    }

    Sort(SignalCount, Signals, &Pool);

    i32 IndexA;
    i32 IndexB;
    for(i32 I=0; I<SignalCount; ++I)
    {
        if(Equals(Signals[I], "[[2]]"))
        {
            IndexA = I + 1;
        }
        else if(Equals(Signals[I], "[[6]]"))
        {
            IndexB = I + 1;
        }
    }

    i32 DistressCode = IndexA * IndexB;
    TimingEnd(&Timing);
    printf("Distress code is %d x %d = %d\n", IndexA, IndexB, DistressCode);

    return 0;
}

