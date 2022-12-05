/***************************************************/
/*                                                 */
/*    File: 05a.cpp                                */
/* Created: 2022-12-05                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
The expedition can depart as soon as the final supplies have been unloaded from the ships. Supplies are stored in stacks of marked crates, but because the needed supplies are buried under many other crates, the crates need to be rearranged.

The ship has a giant cargo crane capable of moving crates between stacks. To ensure none of the crates get crushed or fall over, the crane operator will rearrange them in a series of carefully-planned steps. After the crates are rearranged, the desired crates will be at the top of each stack.

The Elves don't want to interrupt the crane operator during this delicate procedure, but they forgot to ask her which crate will end up where, and they want to be ready to unload them as soon as possible so they can embark.

They do, however, have a drawing of the starting stacks of crates and the rearrangement procedure (your puzzle input). For example:

    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2

In this example, there are three stacks of crates. Stack 1 contains two crates: crate Z is on the bottom, and crate N is on top. Stack 2 contains three crates; from bottom to top, they are crates M, C, and D. Finally, stack 3 contains a single crate, P.

Then, the rearrangement procedure is given. In each step of the procedure, a quantity of crates is moved from one stack to a different stack. In the first step of the above rearrangement procedure, one crate is moved from stack 2 to stack 1, resulting in this configuration:

[D]
[N] [C]
[Z] [M] [P]
 1   2   3

In the second step, three crates are moved from stack 1 to stack 3. Crates are moved one at a time, so the first crate to be moved (D) ends up below the second and third crates:

        [Z]
        [N]
    [C] [D]
    [M] [P]
 1   2   3

Then, both crates are moved from stack 2 to stack 1. Again, because crates are moved one at a time, crate C ends up below crate M:

        [Z]
        [N]
[M]     [D]
[C]     [P]
 1   2   3

Finally, one crate is moved from stack 1 to stack 2:

        [Z]
        [N]
        [D]
[C] [M] [P]
 1   2   3

The Elves just need to know which crate will end up on top of each stack; in this example, the top crates are C in stack 1, M in stack 2, and Z in stack 3, so you should combine these together and give the Elves the message CMZ.

After the rearrangement procedure completes, what crate ends up on top of each stack?
*/

#include "common.h"

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

int
main(i32 NumArgs, char *Args[])
{
    i32 LineCount;
    str *Lines = ReadLinesFromFile("05.input", &LineCount);

    // Find the empty line seperating the initial stack config
    // from the instructions
    i32 StackLineCount;
    i32 FirstInstructionLine;
    for(i32 I=0; I<LineCount; ++I)
    {
        if(Lines[I].Length == 0)
        {
            StackLineCount = I-1;
            FirstInstructionLine = I+1;
        }
    }

    cratestack Stacks[128];
    i32 StackCount = Lines[StackLineCount].Length/4 + 1;
    for(i32 I=0; I<StackCount; ++I)
    {
        Stacks[I].Size = 0;
    }

    // Initialize the stacks
    for(i32 I=StackLineCount; I-->0;)
    {
        for(i32 S=0; S<StackCount; ++S)
        {
            i32 Index = S * 4 + 1;
            char C = Lines[I].Buffer[Index];
            if(C != ' ')
            {
                Push(Stacks + S, C);
            }
        }
    }

    puts("Initial:");
    PrintStacks(Stacks, StackCount);

    // Run instructions
    for(i32 I=FirstInstructionLine; I<LineCount; ++I)
    {
        instruction Instruction = ParseInstruction(Lines[I]);

        for(i32 J=0; J<Instruction.CrateCount; ++J)
        {
            char Crate = Pop(Stacks + Instruction.From);
            Push(Stacks + Instruction.To, Crate);
        }
    }

    puts("After:");
    PrintStacks(Stacks, StackCount);

    char Output[128];
    for(i32 I=0; I<StackCount; ++I)
    {
        Output[I] = Peek(Stacks + I);
    }

    printf("The stack tops are %.*s\n", StackCount, Output);

    return 0;
}

