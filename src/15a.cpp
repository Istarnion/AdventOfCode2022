/***************************************************/
/*                                                 */
/*    File: 15a.cpp                                */
/* Created: 2022-12-15                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
You feel the ground rumble again as the distress signal leads you to a large network of subterranean tunnels. You don't have time to search them all, but you don't need to: your pack contains a set of deployable sensors that you imagine were originally built to locate lost Elves.

The sensors aren't very powerful, but that's okay; your handheld device indicates that you're close enough to the source of the distress signal to use them. You pull the emergency sensor system out of your pack, hit the big button on top, and the sensors zoom off down the tunnels.

Once a sensor finds a spot it thinks will give it a good reading, it attaches itself to a hard surface and begins monitoring for the nearest signal source beacon. Sensors and beacons always exist at integer coordinates. Each sensor knows its own position and can determine the position of a beacon precisely; however, sensors can only lock on to the one beacon closest to the sensor as measured by the Manhattan distance. (There is never a tie where two beacons are the same distance to a sensor.)

It doesn't take long for the sensors to report back their positions and closest beacons (your puzzle input). For example:

Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3

So, consider the sensor at 2,18; the closest beacon to it is at -2,15. For the sensor at 9,16, the closest beacon to it is at 10,16.

Drawing sensors as S and beacons as B, the above arrangement of sensors and beacons looks like this:

               1    1    2    2
     0    5    0    5    0    5
 0 ....S.......................
 1 ......................S.....
 2 ...............S............
 3 ................SB..........
 4 ............................
 5 ............................
 6 ............................
 7 ..........S.......S.........
 8 ............................
 9 ............................
10 ....B.......................
11 ..S.........................
12 ............................
13 ............................
14 ..............S.......S.....
15 B...........................
16 ...........SB...............
17 ................S..........B
18 ....S.......................
19 ............................
20 ............S......S........
21 ............................
22 .......................B....

This isn't necessarily a comprehensive map of all beacons in the area, though. Because each sensor only identifies its closest beacon, if a sensor detects a beacon, you know there are no other beacons that close or closer to that sensor. There could still be beacons that just happen to not be the closest beacon to any sensor. Consider the sensor at 8,7:

               1    1    2    2
     0    5    0    5    0    5
-2 ..........#.................
-1 .........###................
 0 ....S...#####...............
 1 .......#######........S.....
 2 ......#########S............
 3 .....###########SB..........
 4 ....#############...........
 5 ...###############..........
 6 ..#################.........
 7 .#########S#######S#........
 8 ..#################.........
 9 ...###############..........
10 ....B############...........
11 ..S..###########............
12 ......#########.............
13 .......#######..............
14 ........#####.S.......S.....
15 B........###................
16 ..........#SB...............
17 ................S..........B
18 ....S.......................
19 ............................
20 ............S......S........
21 ............................
22 .......................B....

This sensor's closest beacon is at 2,10, and so you know there are no beacons that close or closer (in any positions marked #).

None of the detected beacons seem to be producing the distress signal, so you'll need to work out where the distress beacon is by working out where it isn't. For now, keep things simple by counting the positions where a beacon cannot possibly be along just a single row.

So, suppose you have an arrangement of beacons and sensors like in the example above and, just in the row where y=10, you'd like to count the number of positions a beacon cannot possibly exist. The coverage from all sensors near that row looks like this:

                 1    1    2    2
       0    5    0    5    0    5
 9 ...#########################...
10 ..####B######################..
11 .###S#############.###########.

In this example, in the row where y=10, there are 26 positions where a beacon cannot be present.

Consult the report from the sensors you just deployed. In the row where y=2000000, how many positions cannot contain a beacon?
*/

#include "common.h"

struct pointset
{
    i32 Size;
    i32 Capacity;
    i32 Mask;

    i32 *Hash;
    i32 *X;
};

static inline u32
HashPoint(i32 X)
{
    u32 Hash = 2166136261u;

    Hash ^= ((u32)X << 8);
    Hash ^= 16777619u;

    return Hash;
}

static void
PointsInsert(pointset *Set, i32 X)
{
    i32 Hash = HashPoint(X);

    Assert(Set->Size < Set->Capacity, "Set overflow");

    i32 Index = Hash & Set->Mask;

    for(i32 I=0; I<Set->Capacity; ++I)
    {
        if(Set->Hash[Index] == 0)
        {
            Set->Hash[Index] = Hash;
            Set->X[Index] = X;
            Set->Size++;
            break;
        }
        else if(Set->X[Index] == X)
        {
            break; // Already contains key
        }

        Index = (Index + 1) & Set->Mask;
    }
}

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

    constexpr i32 Y = 2000000;
    pointset Points = { 0 };
    Points.Capacity = 1 << 26;
    Points.Mask = Points.Capacity - 1;
    Points.X = (i32 *)calloc(Points.Capacity, sizeof(i32));
    Assert(Points.X, "Failed to alloc Points.X");
    Points.Hash = (i32 *)calloc(Points.Capacity, sizeof(i32));
    Assert(Points.Hash, "Failed to alloc Points.Hash");

    pointset Beacons = { 0 };
    Beacons.Capacity = 512;
    Beacons.Mask = Beacons.Capacity - 1;
    Beacons.X = (i32 *)calloc(Beacons.Capacity, sizeof(i32));
    Assert(Beacons.X, "Failed to alloc Beacons.X");
    Beacons.Hash = (i32 *)calloc(Beacons.Capacity, sizeof(i32));
    Assert(Beacons.Hash, "Failed to alloc Beacons.Hash");

    for(i32 I=0; I<LineCount; ++I)
    {
        i32 MaxSpan = abs(BeaconX[I] - SensorX[I]) + abs(BeaconY[I] - SensorY[I]);
        i32 DistToY = abs(SensorY[I] - Y);
        if(DistToY <= MaxSpan)
        {
            i32 Span = MaxSpan - DistToY;
            PointsInsert(&Points, SensorX[I]);
            for(i32 J=0; J<=Span; ++J)
            {
                PointsInsert(&Points, SensorX[I] - Span + J);
                PointsInsert(&Points, SensorX[I] + Span - J);
            }
        }

        if(BeaconY[I] == Y)
        {
            PointsInsert(&Beacons, BeaconX[I]);
        }

    }

    TimingEnd(&Timing);

    printf("%d undetected locations on Y=%d\n", Points.Size - Beacons.Size, Y);

    return 0;
}

