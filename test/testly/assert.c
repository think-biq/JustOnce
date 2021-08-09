
#include "assert.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

void Fail(const char* Name, int bExitOnFail, const char* FailFMT, ...)
{
    fprintf(stdout, "\033[0;31m");
    fprintf(stdout, "Failed: ");
    fprintf(stdout, "\033[0m"); // Reset color.
    fprintf(stdout, "%s.\n\t", Name);

    char FMT[strlen(FailFMT) + 1 + 1];
    sprintf(FMT, "%s\n", FailFMT);

    va_list VarArgs;
    va_start(VarArgs, FailFMT);
    vfprintf(stdout, FMT, VarArgs); // Special case for varadic args.
    va_end(VarArgs);
    
    if (0 != bExitOnFail)
        exit(1);
}

void Assert(int DataSize, const char* Name, int bExitOnFail, const void* Expected, const void* Actual, const char* FailFMT, ...)
{
    int HasError;

    if (0 == DataSize)
    {
        HasError = strcmp((const char*)Expected, (const char*)Actual);
    }
    else
    {
        HasError = memcmp(Expected, Actual, DataSize);
    }

    if (0 != HasError)
    {
        va_list VarArgs;
        va_start(VarArgs, FailFMT);
        Fail(Name, bExitOnFail, FailFMT, VarArgs); // Special case for varadic args.
        va_end(VarArgs);
    }
}