/***************************************************/
/*                                                 */
/*    File: 05b.cpp                                */
/* Created: 2022-12-05                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

/*
As you watch the crane operator expertly rearrange the crates, you notice the process isn't following your prediction.

Some mud was covering the writing on the side of the crane, and you quickly wipe it away. The crane isn't a CrateMover 9000 - it's a CrateMover 9001.

The CrateMover 9001 is notable for many new and exciting features: air conditioning, leather seats, an extra cup holder, and the ability to pick up and move multiple crates at once.

Again considering the example above, the crates begin in the same configuration:

    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

Moving a single crate from stack 2 to stack 1 behaves the same as before:

[D]
[N] [C]
[Z] [M] [P]
 1   2   3

However, the action of moving three crates from stack 1 to stack 3 means that those three moved crates stay in the same order, resulting in this new configuration:

        [D]
        [N]
    [C] [Z]
    [M] [P]
 1   2   3

Next, as both crates are moved from stack 2 to stack 1, they retain their order as well:

        [D]
        [N]
[C]     [Z]
[M]     [P]
 1   2   3

Finally, a single crate is still moved from stack 1 to stack 2, but now it's crate C that gets moved:

        [D]
        [N]
        [Z]
[M] [C] [P]
 1   2   3

In this example, the CrateMover 9001 has put the crates in a totally different order: MCD.

Before the rearrangement process finishes, update your simulation so that the Elves know where they should stand to be ready to unload the final supplies. After the rearrangement procedure completes, what crate ends up on top of each stack?
*/

#include "common.h"
#include "05.h"

int
main(i32 NumArgs, char *Args[])
{
    timing Timing;
    TimingStart(&Timing);

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

    TimingPostParsing(&Timing);

    // Run instructions
    for(i32 I=FirstInstructionLine; I<LineCount; ++I)
    {
        instruction Instruction = ParseInstruction(Lines[I]);

        char Claw[128];
        i32 ClawSize = 0;
        for(i32 J=0; J<Instruction.CrateCount; ++J)
        {
            Claw[ClawSize++] = Pop(Stacks + Instruction.From);
        }

        for(i32 J=0; J<Instruction.CrateCount; ++J)
        {
            Push(Stacks + Instruction.To, Claw[--ClawSize]);
        }
    }

    char Output[128];
    for(i32 I=0; I<StackCount; ++I)
    {
        Output[I] = Peek(Stacks + I);
    }

    TimingEnd(&Timing);
    printf("The stack tops are %.*s\n", StackCount, Output);

    return 0;
}

