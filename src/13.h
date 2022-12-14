/***************************************************/
/*                                                 */
/*    File: 13.h                                   */
/* Created: 2022-12-13                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D13_H_
#define D13_H_

constexpr u32 PoolCapacity = 1024;
constexpr i32 Capacity = 8; // Capacity of each list

struct value
{
    i32 Size;
    value *Values[Capacity];
};

static inline bool
IsList(value *Val)
{
    return Val->Size >= 0;
}

static inline i32
ToNumber(value *Val)
{
    Assert(!IsList(Val), "Expected number");
    return (i32)((uintptr_t)Val->Values[0]);
}


static inline value *
AllocList(u32 *PoolSize, value *Pool)
{
    Assert(*PoolSize < PoolCapacity, "Value pool overflow");
    value *Result = Pool + *PoolSize;
    *PoolSize += 1;
    Result->Size = 0;
    return Result;
}

static inline value *
AllocNumber(u32 *PoolSize, value *Pool, i32 N)
{
    Assert(*PoolSize < PoolCapacity, "Value pool overflow");
    value *Result = Pool + *PoolSize;
    *PoolSize += 1;
    Result->Size = -1;
    Result->Values[0] = (value *)((uintptr_t)N);
    return Result;
}

static inline void
ConvertToList(value *Val, u32 *PoolSize, value *Pool)
{
    Assert(!IsList(Val), "Expected number");
    value *NewNumber = AllocNumber(PoolSize, Pool, ToNumber(Val));
    Val->Size = 1;
    Val->Values[0] = NewNumber;
}

static inline void
Add(value *List, value *Val)
{
    Assert(IsList(List), "List is not a list");
    Assert(List->Size < Capacity, "List overflow");
    List->Values[List->Size++] = Val;
}

static inline bool
IsNumber(char C)
{
    return C >= '0' && C <= '9';
}

static value *
ParseLine(str Line, u32 *PoolSize, value *Pool)
{
    value *Root = AllocList(PoolSize, Pool);

    value *ListStack[32];
    i32 StackDepth = 1;
    ListStack[0] = Root;

    for(i32 I=1; I<Line.Length-1; ++I)
    {
        if(Line.Buffer[I] == '[')
        {
            Assert(StackDepth < 32, "List stack overflow");
            value *NewList = AllocList(PoolSize, Pool);
            Add(ListStack[StackDepth-1], NewList);
            ListStack[StackDepth++] = NewList;
        }
        else if(Line.Buffer[I] == ']')
        {
            Assert(StackDepth > 0, "List stack underflow");
            --StackDepth;
        }
        else if(IsNumber(Line.Buffer[I]))
        {
            i32 N = Line.Buffer[I] - '0';
            if(IsNumber(Line.Buffer[I-1]))
            {
                value *CurrentList = ListStack[StackDepth-1];
                value *Val = CurrentList->Values[CurrentList->Size-1];
                Assert(!IsList(Val), "Expected Val to be a number");
                i32 PrevValue = ToNumber(Val);
                Val->Values[0] = (value *)((uintptr_t)(PrevValue * 10 + N));
            }
            else
            {
                value *Val = AllocNumber(PoolSize, Pool, N);
                Add(ListStack[StackDepth-1], Val);
            }
        }
        else
        {
            Assert(Line.Buffer[I] == ',', "Unexpexted character in line");
        }
    }

    return Root;
}

static void
PrintList(value *Val)
{
    if(IsList(Val))
    {
        printf("[");
        for(i32 I=0; I<Val->Size; ++I)
        {
            PrintList(Val->Values[I]);
            if(I < Val->Size-1)
            {
                printf(",");
            }
        }

        printf("]");
    }
    else
    {
        printf("%d", ToNumber(Val));
    }
}

static i32
Compare(i32 Left, i32 Right)
{
    if(Left < Right) return -1;
    if(Left > Right) return  1;
    return 0;
}

static i32
Compare(value *Left, value *Right, u32 *PoolSize, value *Pool)
{
    if(!IsList(Left) && !IsList(Right))
    {
        return Compare(ToNumber(Left), ToNumber(Right));
    }
    else if(IsList(Left) && !IsList(Right))
    {
        ConvertToList(Right, PoolSize, Pool);
        return Compare(Left, Right, PoolSize, Pool);
    }
    else if(IsList(Right) && !IsList(Left))
    {
        ConvertToList(Left, PoolSize, Pool);
        return Compare(Left, Right, PoolSize, Pool);
    }
    else
    {
        for(i32 I=0; I < Left->Size || I < Right->Size; ++I)
        {
            if(I >= Left->Size) // Left ran out
            {
                return -1;
            }
            else if(I >= Right->Size) // Right ran out
            {
                return 1;
            }
            else
            {
                i32 C = Compare(Left->Values[I], Right->Values[I], PoolSize, Pool);
                if(C) return C;
            }
        }

        return 0;
    }
}

#endif /* end of include guard: D13_H_ */

