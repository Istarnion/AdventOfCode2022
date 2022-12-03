/***************************************************/
/*                                                 */
/*    File: 02.h                                   */
/* Created: 2022-12-02                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D02_H_
#define D02_H_

enum rps
{
    ROCK,
    PAPER,
    SCISSORS
};

enum result
{
    DRAW,
    WIN,
    LOOSE
};

static inline rps
ToRPS(char C)
{
    rps Result = ROCK;
    if(C == 'A' || C == 'X')
    {
        Result = ROCK;
    }
    else if(C == 'B' || C == 'Y')
    {
        Result = PAPER;
    }
    else if(C == 'C' || C == 'Z')
    {
        Result = SCISSORS;
    }
    else
    {
        Assert(false, "Invalid character passed to ToRPS");
    }

    return Result;
}

static inline result
ToResult(char C)
{
    result Result = DRAW;
    switch(C)
    {
        case 'X': Result = LOOSE; break;
        case 'Y': Result = DRAW; break;
        case 'Z': Result = WIN; break;
        default: Assert(false, "Invalid character passed to ToResult");
    }

    return Result;
}

static inline result
RPS(rps A, rps B)
{
    i32 Result = ((i32)A - (i32)B) % 3;
    if(Result < 0) Result = Result + 3;
    return (result)Result;
}

static inline rps
ReverseRPS(result Wanted, rps Against)
{
    /*
    DRAW - ROCK -> ROCK

    WIN

    LOOSE
    */

    if(Wanted == DRAW)
    {
        return Against;
    }
    else if(Wanted == WIN)
    {
        return (rps)((Against + 1) % 3);
    }
    else
    {
        i32 Move = (Against - 1) % 3;
        if(Move < 0)
        {
            Move = Move + 3;
        }

        return (rps)Move;
    }
}

#endif /* end of include guard: D02_H_ */

