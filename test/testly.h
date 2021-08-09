
#ifndef TESTLY_H_
#define TESTLY_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#define RUN_TEST(Name) \
{ \
    Name(); \
    fprintf(stdout, "\033[0;32m"); \
    fprintf(stdout, "Passed: "); \
    fprintf(stdout, "\033[0m"); \
    fprintf(stdout, "%s.\n", #Name); \
}

void Assert(int DataSize, const char* Name, const void* Expected, const void* Actual, const char* FailFMT, ...)
{
#ifndef ASSERT_DISABLED
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
        
        exit(1);
    }
#endif
}

#endif