/***************************************************/
/*                                                 */
/*    File: 11.h                                   */
/* Created: 2022-12-11                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D11_H_
#define D11_H_

constexpr i32 MaxItems = 256;

enum update_op
{
    OP_ADD,
    OP_MUL,
    OP_EXP
};

struct monkey
{
    u32 ItemCount;
    u64 Items[MaxItems];

    update_op Operator;
    u64 UpdateConstant;

    u64 Test;
    i32 IfTrue;
    i32 IfFalse;

    u64 InspectionCount;
};

static inline void
PrintMonkey(const monkey &Monkey)
{
    printf("Items: ");
    for(u32 I=0; I<Monkey.ItemCount; ++I)
    {
        printf("%llu%s", Monkey.Items[I], (I < Monkey.ItemCount-1) ? ", " : "");
    }
    putchar('\n');

    char Operators[3] = { '+', '*', '^' };
    printf("Operation: new = old %c %llu\n", Operators[Monkey.Operator], Monkey.UpdateConstant);

    printf("Test: divisible by %llu\n", Monkey.Test);

    printf("  If true: throw to monkey %d\n", Monkey.IfTrue);
    printf("  If false: throw to monkey %d\n", Monkey.IfFalse);

    printf("Inspected %llu items\n", Monkey.InspectionCount);

    putchar('\n');
}

static void
ParseMonkeys(str *Lines, i32 MonkeyCount, monkey *Monkeys)
{
    for(i32 I=0; I<MonkeyCount; ++I)
    {
        str StartingItemsLine = Lines[I*7 + 1];
        Consume(&StartingItemsLine, "  Starting items: ");
        do
        {
            if(StartingItemsLine.Buffer[0] == ',')
            {
                Consume(&StartingItemsLine, ", ");
            }

            Monkeys[I].Items[Monkeys[I].ItemCount++] = ConsumeInt(&StartingItemsLine);
        }
        while(StartingItemsLine.Length > 0);

        str OperationLine = Lines[I*7 + 2];
        Consume(&OperationLine, "  Operation: new = old ");
        if(OperationLine.Buffer[0] == '+')
        {
            Consume(&OperationLine, "+ ");
            Monkeys[I].Operator = OP_ADD;
            Monkeys[I].UpdateConstant = ConsumeInt(&OperationLine);
        }
        else if(OperationLine.Buffer[0] == '*')
        {
            Consume(&OperationLine, "* ");
            if(StartsWith(OperationLine, "old"))
            {
                Monkeys[I].Operator = OP_EXP;
                Monkeys[I].UpdateConstant = 2;
            }
            else
            {
                Monkeys[I].Operator = OP_MUL;
                Monkeys[I].UpdateConstant = ConsumeInt(&OperationLine);
            }
        }
        else Assert(false, "Unknown operator");

        str TestLine = Lines[I*7 + 3];
        Consume(&TestLine, "  Test: divisible by ");
        Monkeys[I].Test = ConsumeInt(&TestLine);

        str TrueLine = Lines[I*7 + 4];
        Consume(&TrueLine, "    If true: throw to monkey ");
        Monkeys[I].IfTrue = ConsumeInt(&TrueLine);

        str FalseLine = Lines[I*7 + 5];
        Consume(&FalseLine, "    If false: throw to monkey ");
        Monkeys[I].IfFalse = ConsumeInt(&FalseLine);
    }
}

#endif /* end of include guard: D11_H_ */

