/***************************************************/
/*                                                 */
/*    File: 11b.cpp                                */
/* Created: 2022-12-11                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
You're worried you might not ever get your items back. So worried, in fact, that your relief that a monkey's inspection didn't damage an item no longer causes your worry level to be divided by three.

Unfortunately, that relief was all that was keeping your worry levels from reaching ridiculous levels. You'll need to find another way to keep your worry levels manageable.

At this rate, you might be putting up with these monkeys for a very long time - possibly 10000 rounds!

With these new rules, you can still figure out the monkey business after 10000 rounds. Using the same example above:

== After round 1 ==
Monkey 0 inspected items 2 times.
Monkey 1 inspected items 4 times.
Monkey 2 inspected items 3 times.
Monkey 3 inspected items 6 times.

== After round 20 ==
Monkey 0 inspected items 99 times.
Monkey 1 inspected items 97 times.
Monkey 2 inspected items 8 times.
Monkey 3 inspected items 103 times.

== After round 1000 ==
Monkey 0 inspected items 5204 times.
Monkey 1 inspected items 4792 times.
Monkey 2 inspected items 199 times.
Monkey 3 inspected items 5192 times.

== After round 2000 ==
Monkey 0 inspected items 10419 times.
Monkey 1 inspected items 9577 times.
Monkey 2 inspected items 392 times.
Monkey 3 inspected items 10391 times.

== After round 3000 ==
Monkey 0 inspected items 15638 times.
Monkey 1 inspected items 14358 times.
Monkey 2 inspected items 587 times.
Monkey 3 inspected items 15593 times.

== After round 4000 ==
Monkey 0 inspected items 20858 times.
Monkey 1 inspected items 19138 times.
Monkey 2 inspected items 780 times.
Monkey 3 inspected items 20797 times.

== After round 5000 ==
Monkey 0 inspected items 26075 times.
Monkey 1 inspected items 23921 times.
Monkey 2 inspected items 974 times.
Monkey 3 inspected items 26000 times.

== After round 6000 ==
Monkey 0 inspected items 31294 times.
Monkey 1 inspected items 28702 times.
Monkey 2 inspected items 1165 times.
Monkey 3 inspected items 31204 times.

== After round 7000 ==
Monkey 0 inspected items 36508 times.
Monkey 1 inspected items 33488 times.
Monkey 2 inspected items 1360 times.
Monkey 3 inspected items 36400 times.

== After round 8000 ==
Monkey 0 inspected items 41728 times.
Monkey 1 inspected items 38268 times.
Monkey 2 inspected items 1553 times.
Monkey 3 inspected items 41606 times.

== After round 9000 ==
Monkey 0 inspected items 46945 times.
Monkey 1 inspected items 43051 times.
Monkey 2 inspected items 1746 times.
Monkey 3 inspected items 46807 times.

== After round 10000 ==
Monkey 0 inspected items 52166 times.
Monkey 1 inspected items 47830 times.
Monkey 2 inspected items 1938 times.
Monkey 3 inspected items 52013 times.

After 10000 rounds, the two most active monkeys inspected items 52166 and 52013 times. Multiplying these together, the level of monkey business in this situation is now 2713310158.

Worry levels are no longer divided by three after each item is inspected; you'll need to find another way to keep your worry levels manageable. Starting again from the initial state in your puzzle input, what is the level of monkey business after 10000 rounds?
*/

#include "common.h"
#include "11.h"

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("11.input", &LineCount);

    monkey Monkeys[8];
    memset(Monkeys, 0, sizeof(Monkeys));

    ParseMonkeys(Lines, 8, Monkeys);

    u64 Supermod = 1;
    for(i32 I=0; I<8; ++I)
    {
        if(Supermod % (u64)Monkeys[I].Test)
        {
            Supermod *= (u64)Monkeys[I].Test;
        }
    }

    for(i32 Round=0; Round<10000; ++Round)
    {
        for(i32 I=0; I<8; ++I)
        {
            for(u32 J=0; J<Monkeys[I].ItemCount; ++J)
            {
                // Inspect
                u64 Item = Monkeys[I].Items[J];

                if(Monkeys[I].Operator == OP_ADD)
                {
                    Item += Monkeys[I].UpdateConstant;
                }
                else if(Monkeys[I].Operator == OP_MUL)
                {
                    Item *= Monkeys[I].UpdateConstant;
                }
                else
                {
                    Item *= Item;
                }

                // Throw
                i32 Target;
                if((Item % Monkeys[I].Test) == 0)
                {
                    Target = Monkeys[I].IfTrue;
                }
                else
                {
                    Target = Monkeys[I].IfFalse;
                }

                Monkeys[Target].Items[Monkeys[Target].ItemCount++] = Item % Supermod;
            }

            Monkeys[I].InspectionCount += (u64)Monkeys[I].ItemCount;
            Monkeys[I].ItemCount = 0;
        }
    }

    u64 Max[2] = { 0, 0 };
    for(i32 I=0; I<8; ++I)
    {
        u64 IC = Monkeys[I].InspectionCount;
        if(IC > Max[1])
        {
            Max[0] = Max[1];
            Max[1] = IC;
        }
        else if(IC > Max[0])
        {
            Max[0] = IC;
        }
    }

    u64 MonkeyBusiness = Max[0] * Max[1];
    printf("Monkey business is %llu * %llu = %llu\n", Max[0], Max[1], MonkeyBusiness);

    return 0;
}

