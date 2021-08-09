
#include "key.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <baseencode/baseencode.h>
#include "misc.h"

void NormalizeKey(char** Key)
{
    const size_t RequiredKeyLength = 32;
    const size_t KeyLength = strlen(*Key);
    const int MissingKeyCharacters = RequiredKeyLength - KeyLength;

    if (0 < MissingKeyCharacters)
    {
        char Appendix[MissingKeyCharacters];
        for (size_t Index = 0; Index < MissingKeyCharacters; ++Index)
        {
            Appendix[Index] = '=';
        }

        char* NewKey = calloc(1, RequiredKeyLength + 1);
        strcat(NewKey, *Key);
        strcat(NewKey, Appendix);
        NewKey[RequiredKeyLength] = '\0';

        ToUpperCase(&NewKey);

        free(*Key);
        *Key = NewKey;
    }
    else if (0 > MissingKeyCharacters)
    {        
        char* NewKey = malloc(RequiredKeyLength + 1);
        strncpy(NewKey, *Key, RequiredKeyLength);
        NewKey[RequiredKeyLength] = '\0';

        ToUpperCase(&NewKey);
        
        free(*Key);
        *Key = NewKey;
    }
}

char* GenerateSecretFromSeed(const char* Seed)
{
    static size_t RelevantSeedLength = 10;

    if (NULL == Seed)
    {
        return NULL;
    }

    const size_t SeedLength = strlen(Seed);
    if (RelevantSeedLength > SeedLength)
    {
        return NULL;
    }

    char* Secret = Hexify((uint8_t*)Seed, RelevantSeedLength);

    ToUpperCase(&Secret);

    return Secret;
}

char* GenerateSecret()
{
    /*
    static const int RequiredSize = 10;

    int Catch = FMath::Rand();
    int Ball = FMath::Rand() + Catch;
    FString Base = FString::Printf(TEXT("%05d"), Catch);
    Base.Append(FString::Printf(TEXT("%05d"), Ball));

    FString Seed = Base.Right(RequiredSize);
    GenerateKeyFromSeed(bValid, Key, Seed);
    */
    return NULL;
}

char* GenerateKeyFromSecret(const char* Secret)
{
    if (NULL == Secret)
    {
        return NULL;
    }

    baseencode_error_t ErrorCode;
    char* Key = base32_encode((unsigned char*)Secret, strlen(Secret), &ErrorCode);
    if (SUCCESS != ErrorCode)
    {
        return NULL;
    }

    return Key;
}

char* GenerateKeyFromSeed(const char* Seed)
{
    char* Secret = GenerateSecretFromSeed(Seed);
    char* Key = GenerateKeyFromSecret(Secret);
    free(Secret);

    return Key;
}

char* GenerateKey()
{
    return NULL;
}