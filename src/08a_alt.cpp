#include "common.h"

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

    i32 LineCount;
    str *Lines = ReadLinesFromFile("08.input", &LineCount);

    i32 Width = Lines[0].Length;
    i32 Height = LineCount;
    char *Set = (char *)malloc(Width * Height);
    memset(Set, 0, Width*Height);

    // Top -> bottom
    for(i32 X=0; X<Width; ++X)
    {
        i32 max = 0;
        for(i32 Y=0; Y<Height; ++Y)
        {
            i32 h = Lines[Y].Buffer[X];
            if(Y == 0 || Y == Height-1 || h > max)
            {
                max = h;
                Set[X + Y * Width] = 1;
            }
        }
    }

    // Bottom -> top
    for(i32 X=0; X<Width; ++X)
    {
        i32 max = 0;
        for(i32 Y=Height; Y-->0;)
        {
            i32 h = Lines[Y].Buffer[X];
            if(Y == 0 || Y == Height-1 || h > max)
            {
                max = h;
                Set[X + Y * Width] = 1;
            }
        }
    }

    // Left -> right
    for(i32 Y=0; Y<Height; ++Y)
    {
        i32 max = 0;
        for(i32 X=0; X<Width; ++X)
        {
            i32 h = Lines[Y].Buffer[X];
            if(X == 0 || X == Width-1 || h > max)
            {
                max = h;
                Set[X + Y * Width] = 1;
            }
        }
    }

    // Right -> left
    for(i32 Y=0; Y<Height; ++Y)
    {
        i32 max = 0;
        for(i32 X=Width; X-->0;)
        {
            i32 h = Lines[Y].Buffer[X];
            if(X == 0 || X == Width-1 || h > max)
            {
                max = h;
                Set[X + Y * Width] = 1;
            }
        }
    }

    i32 VisibleTrees = 0;
    for(i32 I=0; I<Width*Height; ++I)
    {
        VisibleTrees += (i32)Set[I];
    }

    TimingEnd(&Timing);

    printf("%d\n", VisibleTrees);

    return 0;
}

