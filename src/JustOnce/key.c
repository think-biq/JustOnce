
#include "key.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <baseencode/baseencode.h>
#include "misc.h"

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

    char* Secret = malloc(RelevantSeedLength*2 + 1);
    for (size_t DataIndex = 0; DataIndex < RelevantSeedLength; ++DataIndex)
    {
        const char DataPart = Seed[DataIndex];
        char HexValue[3];
        snprintf(HexValue, 3, "%02x", DataPart);
        strcat(Secret, HexValue);
    }
    Secret[RelevantSeedLength*2] = '\0';

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