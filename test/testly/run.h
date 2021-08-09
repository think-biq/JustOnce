
#ifndef TESTLY_H_
#define TESTLY_H_

#include <stdio.h>

#define RUN_TEST(Name) \
{ \
    Name(); \
    fprintf(stdout, "\033[0;32m"); \
    fprintf(stdout, "Passed: "); \
    fprintf(stdout, "\033[0m"); \
    fprintf(stdout, "%s.\n", #Name); \
}

#endif