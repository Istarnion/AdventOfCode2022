/***************************************************/
/*                                                 */
/*    File: 04.h                                   */
/* Created: 2022-12-04                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D04_H_
#define D04_H_

static void
ParsePairs(str Line, i32 *MinA, i32 *MaxA, i32 *MinB, i32 *MaxB)
{
    *MinA = ToInt(Line);

    while(*Line.Buffer != '-')
    {
        Line.Buffer++;
        Line.Length--;
        Assert(Line.Length > 0, "Ran out of string after first number in ParsePairs");
    }

    // Skip hyphen
    Line.Buffer++;
    Line.Length--;
    Assert(Line.Length > 0, "Ran out of string after first hyphen in ParsePairs");

    *MaxA = ToInt(Line);

    while(*Line.Buffer != ',')
    {
        Line.Buffer++;
        Line.Length--;
        Assert(Line.Length > 0, "Ran out of string after second number in ParsePairs");
    }

    // Skip comma
    Line.Buffer++;
    Line.Length--;
    Assert(Line.Length > 0, "Ran out of string after comma in ParsePairs");

    *MinB = ToInt(Line);

    while(*Line.Buffer != '-')
    {
        Line.Buffer++;
        Line.Length--;
        Assert(Line.Length > 0, "Ran out of string after third number in ParsePairs");
    }

    // Skip hyphen
    Line.Buffer++;
    Line.Length--;
    Assert(Line.Length > 0, "Ran out of string after second hyphen in ParsePairs");

    *MaxB = ToInt(Line);
}

#endif /* end of include guard: D04_H_ */

