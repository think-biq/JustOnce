
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

    va_list FailArgs;
    va_start(FailArgs, FailFMT);
    vfprintf(stdout, FMT, FailArgs); // Special case for varadic args.
    va_end(FailArgs);
    
    if (0 != bExitOnFail)
        exit(1);
}

void VFail(const char* Name, int bExitOnFail, const char* FailFMT, va_list FailArgs)
{
    fprintf(stdout, "\033[0;31m");
    fprintf(stdout, "Failed: ");
    fprintf(stdout, "\033[0m"); // Reset color.
    fprintf(stdout, "%s.\n\t", Name);

    char FMT[strlen(FailFMT) + 1 + 1];
    sprintf(FMT, "%s\n", FailFMT);
    vfprintf(stdout, FMT, FailArgs); // Special case for varadic args.
    
    if (0 != bExitOnFail)
        exit(1);
}

void Assert(int DataSize, const char* Name, int bExitOnFail, const void* Expected, const void* Actual, const char* FailFMT, ...)
{
    int HasError = 1;

    if (NULL != Expected && NULL != Actual)
    {
        if (0 == DataSize)
        {
            HasError = strcmp((const char*)Expected, (const char*)Actual);
        }
        else
        {
            HasError = memcmp(Expected, Actual, DataSize);
        }     
    }

    if (0 != HasError)
    {
        va_list VarArgs;
        va_start(VarArgs, FailFMT);
        if (NULL == Name)
        {
            VFail("NULL", bExitOnFail, FailFMT, VarArgs);
        }
        else
        {
            VFail(Name, bExitOnFail, FailFMT, VarArgs);
        }
        va_end(VarArgs);
    }   
}