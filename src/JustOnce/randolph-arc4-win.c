// Copyright (c) blurryroots innovation qanat OÜ

#if defined(_WIN32)
#pragma message ( "Going to define randolph for windows ..." )

#if !defined(USE_BCRYPT)
#define USE_BCRYPT 1
#endif

#include <stdint.h>
#include <windows.h>
#if USE_BCRYPT
#include <bcrypt.h>
#else
#include <wincrypt.h>
#endif

BOOL bGlobal_ProviderReady = FALSE;
BOOL Global_bHasSeed = FALSE;
uint32_t Global_Seed = 0;
#if USE_BCRYPT
    BCRYPT_ALG_HANDLE Global_Provider = NULL;
#else
    HCRYPTPROV        Global_Provider = NULL;
#endif

int
randolph_startup(void)
{
#if USE_BCRYPT
    bGlobal_ProviderReady = BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(&Global_Provider,
        BCRYPT_RNG_ALGORITHM,
        NULL, 
        0
    ));
#else
    bGlobal_ProviderRead = CryptAcquireContextA(&Global_Provider,
        NULL,
        NULL, //(LPCWSTR)L"Microsoft Base Cryptographic Provider v1.0", // From example.
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT
    );
#endif

    return bGlobal_ProviderReady;
}

int
randolph_shutdown(void)
{
    BOOL bShutdownOK;

#if USE_BCRYPT
    bShutdownOK = BCRYPT_SUCCESS(BCryptCloseAlgorithmProvider(Global_Provider, 0));
#else
    bShutdownOK = CryptReleaseContext(Global_Provider, 0);
#endif

    bGlobal_ProviderReady = FALSE;

    return bShutdownOK;
}

int
randolph_is_ready(void)
{
    return bGlobal_ProviderReady;
}

int
randolph_seed(uint32_t seed)
{
    Global_Seed = seed;
    Global_bHasSeed = TRUE;
}

void
_randolph_bytes(BYTE* RandomBytes, size_t Size)
{
#if USE_BCRYPT
    BCRYPT_SUCCESS(BCryptGenRandom(Global_Provider, RandomBytes, sizeof(int), 0));
#else
    CryptGenRandom(Global_Provider, sizeof(int), RandomBytes);
#endif
}

uint32_t
randolph_int(void)
{
    uint32_t Result = 0;
    BYTE     RandomBytes[sizeof(uint32_t)] = { [2] = 23, [3] = 23 };

    if (Global_bHasSeed)
    {
        // Initializes the buffer with a specific seed.
        memcpy(RandomBytes, &Global_Seed, sizeof(uint32_t));
    }
#if 0
    else
    {
        ZeroMemory(RandomBytes, sizeof(uint32_t));        
    }
#endif

    if (bGlobal_ProviderReady)
    {
        _randolph_bytes(RandomBytes, sizeof(uint32_t));
    }
    memcpy(&Result, RandomBytes, sizeof(uint32_t));

    return Result;
}

uint32_t
randolph_int_uniform(uint32_t upper_bound)
{
    return randolph_int() % upper_bound;
}

int
randolph_buffer(void* buffer, size_t buffer_size)
{
    if (NULL == buffer || 0 == buffer_size) return 0;

    memset(buffer, 0, buffer_size);

    if (bGlobal_ProviderReady)
    {
        _randolph_bytes(buffer, buffer_size);
        return 1;
    }

    return 0;
}

#if WITH_ARC4RANDOM
#pragma message ( "I already have arc4, thank you! :)" )
#else
#if defined(RANDOLPH_DEFINE_ARC4)
#pragma message ( "Going to define arc4 for you ..." )

uint32_t
arc4random(void)
{
    return randolph_int();
}

void
arc4random_buf(void *buf, size_t nbytes)
{
    randolph_buffer(buf, nbytes);
}

uint32_t
arc4random_uniform(uint32_t upper_bound)
{
    return arc4random() % upper_bound;
}

#endif

#endif

#endif