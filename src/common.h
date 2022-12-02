/***************************************************/
/*                                                 */
/*    File: common.h                               */
/* Created: 2022-12-02                             */
/*  Author: Istarnion                              */
/*                                                 */
/***************************************************/

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float r32;
typedef double r64;

#define CRASH (*((volatile int *)0) = 1)
#define Assert(stmt, msg) if(!(stmt)) { fprintf(stderr, "%s (%d) - Assertion Failed: %s\n", __FILE__, __LINE__, msg); CRASH; }
#define UNREACHABLE do { fprintf(stderr, "%s (%d) - Unreachable code reached\n", __FILE__, __LINE__); CRASH; } while(0)

struct str
{
    char *Buffer;
    i32 Length;
};

#define FMT(_str) (_str).Length, (_str).Buffer

static inline i32
ToInt(const str &Str)
{
    return (i32)strtol(Str.Buffer, NULL, 10);
}

static str
ReadEntireFile(const char *Filename)
{
    str Result = { 0 };

    FILE *File = fopen(Filename, "r");
    Assert(File, "Failed to open file");

    fseek(File, 0, SEEK_END);
    u64 FileLength = ftell(File);
    rewind(File);

    char *Buffer = (char *)malloc(FileLength + 1);
    Assert(Buffer, "Failed to allocate buffer for file contents");

    u64 BytesRead = fread(Buffer, FileLength, 1, File);
    Assert(BytesRead == 1, "Failed to read all of file");

    Buffer[FileLength] = 0;

    fclose(File);

    Result.Buffer = Buffer;
    Result.Length = (i32)FileLength;

    return Result;
}

static str *
ReadLinesFromFile(const char *Filename, i32 *LineCount)
{
    str FileContents = ReadEntireFile(Filename);
    i32 Count = 0;
    char *C = FileContents.Buffer;
    while(*C)
    {
        if(*C == '\n')
        {
            Count++;
        }

        C++;
    }

    str *Lines = (str *)calloc(Count, sizeof(str));
    Assert(Lines, "Failed to allocate line buffer");

    C = FileContents.Buffer;
    for(i32 LineIndex = 0; LineIndex < Count; LineIndex++)
    {
        Lines[LineIndex].Buffer = C;
        while(*C != '\n')
        {
            Lines[LineIndex].Length++;
            C++;
        }

        C++; // Skip the '\n'
    }

    if(LineCount)
    {
        *LineCount = Count;
    }

    return Lines;
}

#endif /* end of include guard: COMMON_H_ */

