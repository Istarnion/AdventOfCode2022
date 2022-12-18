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
#include <time.h>

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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"

#define CRASH (*((volatile int *)0) = 1)
#define Assert(stmt, msg) if(!(stmt)) { fprintf(stderr, "%s (%d) - Assertion Failed: %s\n", __FILE__, __LINE__, msg); CRASH; }
#define UNREACHABLE do { fprintf(stderr, "%s (%d) - Unreachable code reached\n", __FILE__, __LINE__); CRASH; } while(0)

struct timing
{
    timespec Start;
    timespec PastParsing;
};

static inline void
TimingStart(timing *Timing)
{
    clock_gettime(CLOCK_MONOTONIC, &Timing->Start);
    memset(&Timing->PastParsing, 0, sizeof(timespec));
}

static inline void
TimingPostParsing(timing *Timing)
{
    clock_gettime(CLOCK_MONOTONIC, &Timing->PastParsing);
}

static inline void
TimingEnd(timing *Timing)
{
    timespec Now;
    clock_gettime(CLOCK_MONOTONIC, &Now);

    u64 Start = Timing->Start.tv_sec * 1000000000llu + Timing->Start.tv_nsec;
    u64 PastParse = Timing->PastParsing.tv_sec * 1000000000llu + Timing->PastParsing.tv_nsec;
    u64 End = Now.tv_sec * 1000000000llu + Now.tv_nsec;

    if(Timing->PastParsing.tv_sec != 0 || Timing->PastParsing.tv_nsec != 0)
    {
        u64 ParsingTime = (PastParse - Start) / 1000llu;
        u64 SolveTime = (End - PastParse) / 1000llu;
        printf("Parsing: %10llu µs\n", ParsingTime);
        printf("Solve:   %10llu µs\n", SolveTime);
    }

    u64 TotalTime = (End - Start) / 1000llu;
    printf("Total:   %10llu µs\n", TotalTime);
}

static inline i32
Sign(i32 I)
{
    if(I < 0) return -1;
    if(I > 0) return 1;
    return 0;
}

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

static inline char
Advance(str *String)
{
    Assert(String->Length > 0, "Moving past end of string");
    char Result = String->Buffer[0];
    String->Buffer++;
    String->Length--;
    return Result;
}

static void
Consume(str *String, const char *Expected)
{
    i32 ExpectedLength = strnlen(Expected, String->Length);
    for(i32 I=0; I<ExpectedLength; ++I)
    {
        Assert(String->Buffer[I] == Expected[I], "String did not match expected");
    }

    String->Buffer += ExpectedLength;
    String->Length -= ExpectedLength;
}

static i32
ConsumeInt(str *String)
{
    char *EndPtr;
    i32 Result = strtol(String->Buffer, &EndPtr, 10);
    String->Length -= (EndPtr - String->Buffer);
    String->Buffer = EndPtr;
    return Result;
}

static bool
StartsWith(const str &String, const char *Prefix)
{
    bool Result = true;
    i32 PrefixLength = strnlen(Prefix, String.Length);
    for(i32 I=0; I<PrefixLength; ++I)
    {
        if(String.Buffer[I] != Prefix[I])
        {
            Result = false;
            break;
        }
    }

    return Result;
}

static bool
Equals(const str &A, const str &B)
{
    bool Result = true;
    if(A.Length == B.Length)
    {
        for(i32 I=0; I<A.Length; ++I)
        {
            if(A.Buffer[I] != B.Buffer[I])
            {
                Result = false;
                break;
            }
        }
    }
    else
    {
        Result = false;
    }

    return Result;
}

static bool
Equals(const str &String, const char *Other)
{
    bool Result = true;
    i32 OtherLength = strnlen(Other, String.Length);
    if(OtherLength == String.Length)
    {
        for(i32 I=0; I<OtherLength; ++I)
        {
            if(String.Buffer[I] != Other[I])
            {
                Result = false;
                break;
            }
        }
    }
    else
    {
        Result = false;
    }

    return Result;
}

#pragma clang diagnostic pop

#endif /* end of include guard: COMMON_H_ */

