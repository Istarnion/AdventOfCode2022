/***************************************************/
/*                                                 */
/*    File: 15b.cpp                                */
/* Created: 2022-12-15                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
Your handheld device indicates that the distress signal is coming from a beacon nearby. The distress beacon is not detected by any sensor, but the distress beacon must have x and y coordinates each no lower than 0 and no larger than 4000000.

To isolate the distress beacon's signal, you need to determine its tuning frequency, which can be found by multiplying its x coordinate by 4000000 and then adding its y coordinate.

In the example above, the search space is smaller: instead, the x and y coordinates can each be at most 20. With this reduced search area, there is only a single position that could have a beacon: x=14, y=11. The tuning frequency for this distress beacon is 56000011.

Find the only possible position for the distress beacon. What is its tuning frequency?
*/

#include "common.h"

struct span
{
    i32 Left;
    i32 Right;
};

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("15.input", &LineCount);

    Assert(LineCount < 32, "Too many lines");
    i32 SensorX[32];
    i32 SensorY[32];
    i32 BeaconX[32];
    i32 BeaconY[32];

    for(i32 I=0; I<LineCount; ++I)
    {
        Consume(Lines + I, "Sensor at x=");
        SensorX[I] = ConsumeInt(Lines + I);
        Consume(Lines + I, ", y=");
        SensorY[I] = ConsumeInt(Lines + I);

        Consume(Lines + I, ": closest beacon is at x=");
        BeaconX[I] = ConsumeInt(Lines + I);
        Consume(Lines + I, ", y=");
        BeaconY[I] = ConsumeInt(Lines + I);
    }

    TimingPostParsing(&Timing);

    constexpr i32 Width = 4000001u;
    constexpr i32 Height = 4000001u;

    i32 DistressX = 0;
    i32 DistressY = 0;

    for(i32 Y=0; Y<Height; ++Y)
    {
        i32 SpanCount = 0;
        span Spans[48];

        for(i32 I=0; I<LineCount; ++I)
        {
            i32 MaxSpan = abs(BeaconX[I] - SensorX[I]) + abs(BeaconY[I] - SensorY[I]);
            i32 DistToY = abs(SensorY[I] - Y);

            i32 Left = SensorX[I] - (MaxSpan-DistToY);
            i32 Right = SensorX[I] + (MaxSpan-DistToY);

            if(!(Left > Width || Right < 0) && DistToY <= MaxSpan)
            {
                if(Left < 0) Left = 0;
                if(Right >= Width) Right = Width-1;

                bool Intersects = false;
                for(i32 S=0; S<SpanCount; ++S)
                {
                    if(!(Left > Spans[S].Right || Right < Spans[S].Left))
                    {
                        if(Left < Spans[S].Left) Spans[S].Left = Left;
                        if(Right > Spans[S].Right) Spans[S].Right = Right;

                        Intersects = true;
                    }
                }

                if(!Intersects)
                {
                    Assert(SpanCount < 48, "Spans overflow");
                    Spans[SpanCount++] = { .Left = Left, .Right = Right };
                }
            }
        }

        Assert(SpanCount > 0, "No spans found on this line");

        span Master = Spans[0];
        for(i32 S=1; S<SpanCount*SpanCount; ++S)
        {
            i32 Index = S % SpanCount;
            if(!(Spans[Index].Left > (Master.Right+1) || Spans[Index].Right < (Master.Left-1)))
            {
                if(Spans[Index].Left < Master.Left) Master.Left = Spans[Index].Left;
                if(Spans[Index].Right > Master.Right) Master.Right = Spans[Index].Right;
            }
        }

        if(Master.Left != 0 || Master.Right != (Width-1))
        {
            if(Master.Left != 0)
            {
                DistressX = Master.Left - 1;
            }
            else
            {
                DistressX = Master.Right + 1;
            }

            DistressY = Y;
            break;
        }
    }

    i64 TuningFrequency = 4000000ll * (i64)DistressX + (i64)DistressY;

    TimingEnd(&Timing);

    printf("Distress beacon found at x=%d, y=%d. Tuning frequency=%lld\n",
           DistressX, DistressY, TuningFrequency);

    return 0;
}

