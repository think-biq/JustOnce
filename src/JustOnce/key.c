
#include "key.h"

#include "misc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <baseencode.h>

static int Global_bUseSafeRand = 1;

void SetRandomizerSafe(int bUseSafeRand)
{
    Global_bUseSafeRand = bUseSafeRand;
}

int GetRandomNumber()
{
    return Global_bUseSafeRand ? arc4random() : rand();
}

void SetRandomizerSeed(int Seed)
{
    srand(Seed);
}

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
    static const int RequiredSize = 10;

    int Catch = GetRandomNumber();
    int Ball = GetRandomNumber();

    char* Base = calloc(1, 5 + 1);
    snprintf(Base, 6, "%05d", Catch);
    Base[5] = '\0';

    char* Tail = calloc(1, 5 + 1);
    snprintf(Tail, 6, "%05d", Ball);
    Tail[5] = '\0';

    char* Seed = calloc(1, 5 + 5 + 1);
    snprintf(Seed, 11, "%s%s", Base, Tail);
    Seed[5 + 5] = '\0';

    free(Base);
    free(Tail);

    char* Secret = GenerateSecretFromSeed(Seed);
    if (NULL != Secret)
        free(Seed);

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

char* GenerateKeyFromSeed(const char* Seed)
{
    char* Secret = GenerateSecretFromSeed(Seed);
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