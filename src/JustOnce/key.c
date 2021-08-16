
#include "key.h"

#include "misc.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <baseencode.h>
#include <ShaOne/hash.h>

static int Global_bUseSafeRand = 1;

void SetRandomizerSafe(int bUseSafeRand)
{
    Global_bUseSafeRand = bUseSafeRand;
}

int GetRandomNumber()
{
    return Global_bUseSafeRand ? arc4random() : rand();
}

int GetRandomNumberRanged(uint32_t Limit)
{
    return Global_bUseSafeRand ? arc4random_uniform(Limit) : rand() % Limit;
}

void SetRandomizerSeed(int Seed)
{
    srand(Seed);
}

int IsValidKey(const char* Key)
{
    if (NULL == Key)
    {
        return 0;
    }

    size_t KeyLength = strlen(Key);
    if (32 != KeyLength)
    {
        return 0;
    }

    baseencode_error_t err;
    unsigned char* Secret = base32_decode(Key, KeyLength, &err);

    int bIsValid = NULL != Secret
                && SUCCESS == err
                ;

    if (NULL != Secret)
        free(Secret);

    return bIsValid;
}

char* NormalizeKey(const char* Key)
{
    const size_t RequiredKeyLength = 32;
    const size_t KeyLength = strlen(Key);
    const int MissingKeyCharacters = RequiredKeyLength - KeyLength;

    char* NewKey = NULL;

    if (NULL == Key)
    {
        return NewKey;
    }

    if (0 > MissingKeyCharacters)
    {
        return NewKey;
    }

    if (0 < MissingKeyCharacters)
    {
        char Appendix[MissingKeyCharacters];
        for (size_t Index = 0; Index < MissingKeyCharacters; ++Index)
        {
            Appendix[Index] = '=';
        }

        NewKey = calloc(1, RequiredKeyLength + 1);
        strncpy(NewKey, Key, KeyLength);
        strncpy(NewKey+KeyLength, Appendix, MissingKeyCharacters);
        NewKey[RequiredKeyLength] = '\0';
    }
    else
    {        
        NewKey = malloc(RequiredKeyLength + 1);
        strncpy(NewKey, Key, RequiredKeyLength);
        NewKey[RequiredKeyLength] = '\0';
    }

    ToUpperCase(&NewKey);

    return NewKey;
}

char* GenerateSecretFromSeed(const uint8_t* Seed, size_t SeedLength)
{
    static size_t RelevantSeedLength = 10;

    if (NULL == Seed)
    {
        fprintf(stderr, "Given seed is null!\n");
        return NULL;
    }

    if (RelevantSeedLength > SeedLength)
    {
        fprintf(stderr, "Seed size is smaller than 10! (%zu) '%s'\n", SeedLength, Seed);
        return NULL;
    }

    char* Secret = Hexify(Seed, RelevantSeedLength);

    ToUpperCase(&Secret);

    return Secret;
}

char* GenerateSecret()
{
    static const int RequiredSize = 10;
    uint8_t Seed[RequiredSize];

    for (size_t Index = 0; Index < RequiredSize; ++Index)
    {
        Seed[Index] = GetRandomNumberRanged(256);
    }

    char* Secret = GenerateSecretFromSeed(Seed, 10);
    return Secret;
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

char* GenerateKeyFromSeed(const uint8_t* Seed, size_t SeedLength)
{
    char* Secret = GenerateSecretFromSeed(Seed, SeedLength);
    char* Key = GenerateKeyFromSecret(Secret);
    free(Secret);

    return Key;
}

char* GenerateKey()
{
    char* Secret = GenerateSecret();
    char* Key = GenerateKeyFromSecret(Secret);
    free(Secret);

    return Key;
}