/***************************************************/
/*                                                 */
/*    File: 14.h                                   */
/* Created: 2022-12-14                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D14_H_
#define D14_H_

struct wall
{
    i32 PointCount;
    i32 X[32];
    i32 Y[32];
};

static wall *
ParseWalls(i32 LineCount, str *Lines, i32 *MinX, i32 *MaxX, i32 *MaxY)
{
    wall *Walls = (wall *)malloc(LineCount * sizeof(wall));

    *MinX = INT32_MAX;
    *MaxX = 0;
    *MaxY = 0;
    for(i32 I=0; I<LineCount; ++I)
    {
        Walls[I].PointCount = 0;
        while(true)
        {
            i32 X = ConsumeInt(Lines + I);
            Lines[I].Buffer++;
            Lines[I].Length--;
            i32 Y = ConsumeInt(Lines + I);

            if(X < *MinX)
            {
                *MinX = X;
            }

            if(X > *MaxX)
            {
                *MaxX = X;
            }

            if(Y > *MaxY)
            {
                *MaxY = Y;
            }

            Walls[I].X[Walls[I].PointCount] = X;
            Walls[I].Y[Walls[I].PointCount] = Y;
            Walls[I].PointCount++;

            if(Lines[I].Length == 0 || !StartsWith(Lines[I], " -> "))
            {
                break;
            }
            else
            {
                Consume(Lines + I, " -> ");
            }
        }
    }

    return Walls;
}

#endif /* end of include guard: D14_H_ */
