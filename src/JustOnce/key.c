
#include "key.h"

#include "misc.h"
#include "randolph.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <baseencode.h>
#include <ShaOne/hash.h>

enum KeyDefines_Internal {
    REQUIRED_KEY_LENGTH = 32,
    REQUIRED_SECRET_LENGTH = 10,
    MAX_MISSING_CHARACTERS_BUFFER_SIZE = 32
};

static int Global_bUseSafeRand = 1;

void SetRandomizerSafe(int bUseSafeRand)
{
    Global_bUseSafeRand = bUseSafeRand;
}

int GetRandomizerSafe()
{
    return Global_bUseSafeRand;
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
    if (Global_bUseSafeRand)
    {

    }
    else
    {
        srand(Seed);
    }
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
    const size_t KeyLength = strlen(Key);
    const int MissingKeyCharacters = REQUIRED_KEY_LENGTH - KeyLength;

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
        char Appendix[MAX_MISSING_CHARACTERS_BUFFER_SIZE] = { 0 };
        for (size_t Index = 0; Index < MissingKeyCharacters; ++Index)
        {
            Appendix[Index] = '=';
        }

        NewKey = calloc(1, REQUIRED_KEY_LENGTH + 1);
        strncpy(NewKey, Key, KeyLength);
        strncpy(NewKey+KeyLength, Appendix, MissingKeyCharacters);
        NewKey[REQUIRED_KEY_LENGTH] = '\0';
    }
    else
    {        
        NewKey = malloc(REQUIRED_KEY_LENGTH + 1);
        strncpy(NewKey, Key, REQUIRED_KEY_LENGTH);
        NewKey[REQUIRED_KEY_LENGTH] = '\0';
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
    uint8_t Seed[REQUIRED_SECRET_LENGTH];

    for (size_t Index = 0; Index < REQUIRED_SECRET_LENGTH; ++Index)
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