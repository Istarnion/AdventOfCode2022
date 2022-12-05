/***************************************************/
/*                                                 */
/*    File: 05.h                                   */
/* Created: 2022-12-05                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D05_H_
#define D05_H_

struct cratestack
{
    char Data[512];
    i32 Size;
};

static inline char
Peek(cratestack *Stack)
{
    char Result = Stack->Data[Stack->Size-1];
    return Result;
}

static inline char
Pop(cratestack *Stack)
{
    Assert(Stack->Size > 0, "Stack underflow");
    char Result = Stack->Data[--(Stack->Size)];
    return Result;
}

static inline void
Push(cratestack *Stack, char C)
{
    Assert(Stack->Size < 512, "Stack overflow");
    Stack->Data[(Stack->Size)++] = C;
}

static void
PrintStacks(cratestack *Stacks, i32 StackCount)
{
    i32 MaxStackSize = 0;
    for(i32 I=0; I<StackCount; ++I)
    {
        if(Stacks[I].Size > MaxStackSize)
        {
            MaxStackSize = Stacks[I].Size;
        }
    }


    for(i32 L=0; L<MaxStackSize; ++L)
    {
        for(i32 I=0; I<StackCount; ++I)
        {
            if(Stacks[I].Size >= MaxStackSize-L)
            {
                printf("[%c] ", Stacks[I].Data[MaxStackSize - L - 1]);
            }
            else
            {
                printf("    ");
            }
        }

        putchar('\n');
    }

    for(i32 I=0; I<StackCount; ++I)
    {
        printf(" %d  ", I+1);
    }

    putchar('\n');
}

struct instruction
{
    i32 CrateCount;
    i32 From;
    i32 To;
};

static inline instruction
ParseInstruction(str Line)
{
    instruction Result;

    Consume(&Line, "move ");
    Result.CrateCount = ConsumeInt(&Line);
    Consume(&Line, " from ");
    Result.From = ConsumeInt(&Line) - 1;
    Consume(&Line, " to ");
    Result.To = ConsumeInt(&Line) - 1;

    return Result;
}

#endif /* end of include guard: D05_H_ */

