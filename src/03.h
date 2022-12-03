/***************************************************/
/*                                                 */
/*    File: 03.h                                   */
/* Created: 2022-12-03                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D03_H_
#define D03_H_

static inline i32
Priority(char C)
{
    i32 Result = 0;
    if(C >= 'a' && C <= 'z')
    {
        Result = (C - 'a') + 1;
    }
    else if(C >= 'A' && C <= 'Z')
    {
        Result = (C - 'A') + 27;
    }
    else
    {
        Assert(false, "Invalid character passed to Priority");
    }

    return Result;
}

#endif /* end of include guard: D03_H_ */

