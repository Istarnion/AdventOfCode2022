/***************************************************/
/*                                                 */
/*    File: 12.h                                   */
/* Created: 2022-12-12                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D12_H_
#define D12_H_

struct cell
{
    i32 Index;
    i32 Dist;
    i32 Score;
    i32 Height;
    bool Closed;
};

static void
HeapifyDown(i32 HeapSize, cell **Heap, i32 Root = 0)
{
    cell *Left  = (Root*2+1) < HeapSize ? Heap[Root*2+1] : NULL;
    cell *Right = (Root*2+2) < HeapSize ? Heap[Root*2+2] : NULL;

    if(Left && (!Right || Left->Score <= Right->Score))
    {
        if(Left->Score < Heap[Root]->Score)
        {
            Heap[Root*2+1] = Heap[Root];
            Heap[Root] = Left;
            HeapifyDown(HeapSize, Heap, Root*2+1);
        }
    }
    else if(Right)
    {
        if(Right->Score < Heap[Root]->Score)
        {
            Heap[Root*2+2] = Heap[Root];
            Heap[Root] = Right;
            HeapifyDown(HeapSize, Heap, Root*2+2);
        }
    }
}

static void
HeapifyUp(i32 HeapSize, cell **Heap, i32 Root)
{
    if(Root > 0)
    {
        cell *Parent = Root > 0 ? Heap[(Root-1)/2] : NULL;

        if(Parent && Parent->Score > Heap[Root]->Score)
        {
            Heap[(Root-1)/2] = Heap[Root];
            Heap[Root] = Parent;
            HeapifyUp(HeapSize, Heap, (Root-1)/2);
        }
    }
}

static cell *
Pop(i32 *HeapSize, cell **Heap)
{
    cell *Min = Heap[0];
    Heap[0] = Heap[(*HeapSize)-1];
    (*HeapSize)--;
    HeapifyDown(*HeapSize, Heap);
    return Min;
}

#endif /* end of include guard: D12_H_ */
