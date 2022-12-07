/***************************************************/
/*                                                 */
/*    File: 07.h                                   */
/* Created: 2022-12-07                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef D07_H_
#define D07_H_

struct file
{
    str Name;
    i32 Size;
    file *Parent;
    i32 ChildCount;
    file *Children[128];
};

static inline file *
NewFile(file *Pool, i32 *Count)
{
    Assert(*Count < 2000, "Out of files");
    file *Result = Pool + (*Count);
    memset(Result, 0, sizeof(file));
    (*Count)++;
    return Result;
}

static inline void
AppendFile(file *Parent, file *Child)
{
    Assert(Parent->ChildCount < 128, "Parent has too many children");
    Parent->Children[Parent->ChildCount++] = Child;
    Child->Parent = Parent;
}

static inline file *
GetChild(file *File, const str &ChildName)
{
    file *Result = NULL;
    if(Equals(ChildName, ".."))
    {
        Result = File->Parent;
    }
    else
    {
        for(i32 I=0; I<File->ChildCount; ++I)
        {
            if(Equals(File->Children[I]->Name, ChildName))
            {
                Result = File->Children[I];
                break;
            }
        }
    }

    return Result;
}

struct filesystem
{
    file *Root;
    i32 FileCount;
    file Pool[2000];
};

static void
ParseTree(i32 LineCount, str *Lines, filesystem *FileSystem)
{
    file *CWD = NULL;

    for(i32 I=0; I<LineCount; ++I)
    {
        str Line = Lines[I];
        if(StartsWith(Line, "$"))
        {
            Consume(&Line, "$ ");
            if(StartsWith(Line, "cd"))
            {
                Consume(&Line, "cd ");
                if(CWD)
                {
                    file *Child = GetChild(CWD, Line);
                    if(!Child)
                    {
                        Child = NewFile(FileSystem->Pool, &FileSystem->FileCount);
                        Child->Name = Line;
                        AppendFile(CWD, Child);
                    }

                    CWD = Child;
                }
                else
                {
                    FileSystem->Root = NewFile(FileSystem->Pool, &FileSystem->FileCount);
                    FileSystem->Root->Name = Line;
                    CWD = FileSystem->Root;
                }
            }
            else if(StartsWith(Line, "ls"))
            {
                Consume(&Line, "ls");
            }
            else
            {
                Assert(false, "Unknown command");
            }
        }
        // ls output
        else if(StartsWith(Line, "dir"))
        {
            Consume(&Line, "dir ");
            file *Child = GetChild(CWD, Line);
            if(!Child)
            {
                Child = NewFile(FileSystem->Pool, &FileSystem->FileCount);
                Child->Name = Line;
                AppendFile(CWD, Child);
            }

        }
        else
        {
            i32 Size = ConsumeInt(&Line);
            Consume(&Line, " ");
            file *Child = GetChild(CWD, Line);
            if(!Child)
            {
                Child = NewFile(FileSystem->Pool, &FileSystem->FileCount);
                Child->Name = Line;
                Child->Size = Size;
                AppendFile(CWD, Child);
            }

        }
    }
}

static void
PrintTree(file *File, i32 Indent = 0)
{
    printf("%*s%.*s\n", Indent*4, "", FMT(File->Name));
    for(i32 I=0; I<File->ChildCount; ++I)
    {
        PrintTree(File->Children[I], Indent+1);
    }
}

static void
CalcDirSize(file *File)
{
    for(i32 I=0; I<File->ChildCount; ++I)
    {
        if(File->Children[I]->ChildCount)
        {
            CalcDirSize(File->Children[I]);
        }

        File->Size += File->Children[I]->Size;
    }
}

#endif /* end of include guard: D07_H_ */
