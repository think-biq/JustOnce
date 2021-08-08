#include "misc.h"
#include <string.h>
#include <stdlib.h>

char* MakeUpperCase(const char* String)
{
    if (NULL == String)
    {
        return NULL;
    }

    const size_t Length = strlen(String);
    char* Copy = strdup(String);
    ToUpperCase(&Copy);

    return Copy;
}

void ToUpperCase(char** String)
{
    if (NULL == String || NULL == *String)
    {
        return;
    }

    // Make sure key is upper case.
    char* StringPtr = *String;
    for (size_t Index = 0; Index < strlen(StringPtr); ++Index)
    {
        if (StringPtr[Index] >= 'a' && StringPtr[Index] <= 'z')
        {
            StringPtr[Index] = StringPtr[Index] - 32;
        }
    }	
}