/***************************************************/
/*                                                 */
/*    File: 08.h                                   */
/* Created: 2022-12-08                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D08_H_
#define D08_H_

static inline i32
At(i32 X, i32 Y, const str *Lines, i32 Width, i32 Height)
{
    Assert(X >= 0, "X cannot be negative");
    Assert(Y >= 0, "Y cannot be negative");
    Assert(X < Width, "X must be less than Width");
    Assert(Y < Height, "Y must be less than Height");

    i32 Result = (i32)Lines[Y].Buffer[X] - (i32)'0';
    return Result;
}

#endif /* end of include guard: D08_H_ */

