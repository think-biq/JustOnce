#include "misc.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

char* Hexify(uint8_t* Buffer, size_t Count)
{
    if (NULL == Buffer)
    {
        return NULL;
    }

    char* Hash = calloc(1, Count*2+1);
    for (size_t Index = 0; Index < Count; ++Index)
    {
        char Hex[3];
        snprintf(Hex, 3, "%02x", Buffer[Index]);
        strcat(Hash, Hex);
    }

    Hash[Count*2] = '\0';
    return Hash;
}