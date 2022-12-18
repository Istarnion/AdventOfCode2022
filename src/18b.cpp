/***************************************************/
/*                                                 */
/*    File: 18b.cpp                                */
/* Created: 2022-12-18                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
Something seems off about your calculation. The cooling rate depends on exterior surface area, but your calculation also included the surface area of air pockets trapped in the lava droplet.

Instead, consider only cube sides that could be reached by the water and steam as the lava droplet tumbles into the pond. The steam will expand to reach as much as possible, completely displacing any air on the outside of the lava droplet but never expanding diagonally.

In the larger example above, exactly one cube of air is trapped within the lava droplet (at 2,2,5), so the exterior surface area of the lava droplet is 58.

What is the exterior surface area of your scanned lava droplet?
*/

#include "common.h"

static inline i32
Index(i32 X, i32 Y, i32 Z)
{
    return X + Y*32 + Z*32*32;
}

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("18.input", &LineCount);

    i32 MaxX = 0;
    i32 MaxY = 0;
    i32 MaxZ = 0;

    u8 *Voxels = (u8 *)calloc(32*32*32, 1);
    for(i32 I=0; I<LineCount; ++I)
    {
        i32 X = ConsumeInt(Lines + I) + 1;
        Advance(Lines + I);
        i32 Y = ConsumeInt(Lines + I) + 1;
        Advance(Lines + I);
        i32 Z = ConsumeInt(Lines + I) + 1;

        if(X > MaxX) MaxX = X;
        if(Y > MaxY) MaxY = Y;
        if(Z > MaxZ) MaxZ = Z;

        Voxels[Index(X, Y, Z)] = 1;
    }

    TimingPostParsing(&Timing);

    i32 ExposedSides = 0;

    constexpr i32 OpenListCap = 32*32*32;
    i32 OpenListSize = 1;
    i32 OpenListHead = 0;
    i32 *OpenList = (i32 *)calloc(OpenListCap, sizeof(i32));

    while(OpenListSize > 0)
    {
        i32 CurrentIndex = OpenList[OpenListHead++];
        if(OpenListHead >= OpenListCap) OpenListHead = 0;
        OpenListSize--;

        i32 X = CurrentIndex % 32;
        i32 Y = (CurrentIndex / 32) % 32;
        i32 Z = CurrentIndex / (32*32);

        if(X > 0)
        {
            i32 N = Index(X-1, Y, Z);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }

        if(X < 32-1)
        {
            i32 N = Index(X+1, Y, Z);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }

        if(Y > 0)
        {
            i32 N = Index(X, Y-1, Z);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }

        if(Y < 32-1)
        {
            i32 N = Index(X, Y+1, Z);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }

        if(Z > 0)
        {
            i32 N = Index(X, Y, Z-1);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }

        if(Z < 32-1)
        {
            i32 N = Index(X, Y, Z+1);
            u8 V = Voxels[N];
            if(V == 1) ++ExposedSides;
            else if(V == 0)
            {
                Voxels[N] = 0xFF;
                i32 OpenListIndex = (OpenListHead + OpenListSize) % OpenListCap;
                OpenListSize++;
                Assert(OpenListSize <= OpenListCap, "Open list overflow");
                OpenList[OpenListIndex] = N;
            }
        }
    }

    TimingEnd(&Timing);

    printf("There are %d exposed sides on the droplet\n", ExposedSides);

    return 0;
}

