/**
* @file hmac_sha1.c  Implements HMAC-SHA1 as of RFC 2202
*
* Copyright (C) 2010 Creytiv.com
*/
#include <string.h>
#include <stdint.h>
#include <sha/sha.h>
#include <hmac/hmac.h>

/** SHA-1 Block size */
#ifndef SHA_BLOCKSIZE
#define SHA_BLOCKSIZE   (64)
#endif

/**
* Generates HMAC from given data.
* @param Secret Secret key.
* @param SecretLength Lenght of the key.
* @param Data Data to encode.
* @param DataLength Size of the data given.
* @param HMAC Generated HMAC.
* @param HMACLength Size of the hash generated.
*/
void CreateSHA1HMAC(
    const uint8_t *Secret,  /* secret key */
    size_t SecretLength,       /* length of the key in bytes */
    const uint8_t *Data,  /* data */
    size_t DataLength,       /* length of data in bytes */
    uint8_t *HMAC,      /* output buffer, at least "HMACLength" bytes */
    size_t *HMACLength)
{
    if (SHA_BLOCKSIZE < SecretLength)
    {
        SHA_CTX KeyContext;
        uint8_t KeyBuffer[SHA_DIGEST_LENGTH];

        SHA1_Init(&KeyContext);
        SHA1_Update(&KeyContext, Secret, SecretLength);
        SHA1_Final(KeyBuffer, &KeyContext);

        Secret = KeyBuffer;
        SecretLength = SHA_DIGEST_LENGTH;
    }

    uint8_t InnerSHA[SHA_DIGEST_LENGTH], OuterSHA[SHA_DIGEST_LENGTH];

    /**** Inner Digest ****/
    {
        SHA_CTX InnerContext;
        uint8_t BlockBuffer[SHA_BLOCKSIZE];
        const uint8_t Flip = 0x36;

        SHA1_Init(&InnerContext);

        /* Pad the key for inner digest */
        for (size_t Index = 0; Index < SecretLength; ++Index) 
        {
            BlockBuffer[Index] = Secret[Index] ^ Flip;
        }
        for (size_t Index = SecretLength; Index < SHA_BLOCKSIZE; ++Index)
        {
            BlockBuffer[Index] = Flip;
        }

        SHA1_Update(&InnerContext, BlockBuffer, SHA_BLOCKSIZE);
        SHA1_Update(&InnerContext, Data, DataLength);

        SHA1_Final(InnerSHA, &InnerContext);
    }

    /**** Outer Digest ****/
    {
        SHA_CTX OuterContext;
        uint8_t BlockBuffer[SHA_BLOCKSIZE];
        const uint8_t Flip = 0x5c;

        SHA1_Init(&OuterContext);

        /* Pad the key for outter digest */
        for (size_t Index = 0; Index < SecretLength; ++Index)
        {
            BlockBuffer[Index] = Secret[Index] ^ Flip;
        }
        for (size_t Index = SecretLength; Index < SHA_BLOCKSIZE; ++Index)
        {
            BlockBuffer[Index] = Flip;
        }

        SHA1_Update(&OuterContext, BlockBuffer, SHA_BLOCKSIZE);
        SHA1_Update(&OuterContext, InnerSHA, SHA_DIGEST_LENGTH);

        SHA1_Final(OuterSHA, &OuterContext);
    }

    /* truncate and print the results */
    *HMACLength = (SHA_DIGEST_LENGTH < *HMACLength)
        ? SHA_DIGEST_LENGTH
        : *HMACLength
        ;
    memcpy(HMAC, OuterSHA, *HMACLength);
}
