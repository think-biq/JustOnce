/*
The MIT License (MIT)

Copyright (c) blurryroots innovation qanat OÜ

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <string.h>
#include <stdint.h>
#include <sha/sha.h>
#include "hmac.h"

static int64_t DIGITS_POWER[] = { 
    1, 10, 100, 1000, 10000, 100000, 1000000,10000000, 100000000, 1000000000,
    10000000000
};

size_t CreateHMAC(
    uint8_t *HMAC,
    const uint8_t *Secret, const size_t SecretLength,
    const uint8_t *Data, const size_t DataLength    
)
{
    // Thanks to Bob Liu for inspiration.

    size_t EffectiveLength = SecretLength;
    if (SHA_BLOCKSIZE < SecretLength)
    {
        SHA_CTX KeyContext;
        uint8_t KeyBuffer[SHA_DIGEST_LENGTH];

        SHA1_Init(&KeyContext);
        SHA1_Update(&KeyContext, Secret, SecretLength);
        SHA1_Final(KeyBuffer, &KeyContext);

        Secret = KeyBuffer;
        EffectiveLength = SHA_DIGEST_LENGTH;
    }

    uint8_t InnerSHA[SHA_DIGEST_LENGTH], OuterSHA[SHA_DIGEST_LENGTH];

    // Inner Digest
    {
        SHA_CTX InnerContext;
        uint8_t BlockBuffer[SHA_BLOCKSIZE];
        const uint8_t Flip = 0x36;

        SHA1_Init(&InnerContext);

        // Pad the key for inner digest
        for (size_t Index = 0; Index < EffectiveLength; ++Index) 
        {
            BlockBuffer[Index] = Secret[Index] ^ Flip;
        }
        for (size_t Index = EffectiveLength; Index < SHA_BLOCKSIZE; ++Index)
        {
            BlockBuffer[Index] = Flip;
        }

        SHA1_Update(&InnerContext, BlockBuffer, SHA_BLOCKSIZE);
        SHA1_Update(&InnerContext, Data, DataLength);

        SHA1_Final(InnerSHA, &InnerContext);
    }

    // Outer Digest
    {
        SHA_CTX OuterContext;
        uint8_t BlockBuffer[SHA_BLOCKSIZE];
        const uint8_t Flip = 0x5c;

        SHA1_Init(&OuterContext);

        // Pad the key for outter digest
        for (size_t Index = 0; Index < EffectiveLength; ++Index)
        {
            BlockBuffer[Index] = Secret[Index] ^ Flip;
        }
        for (size_t Index = EffectiveLength; Index < SHA_BLOCKSIZE; ++Index)
        {
            BlockBuffer[Index] = Flip;
        }

        SHA1_Update(&OuterContext, BlockBuffer, SHA_BLOCKSIZE);
        SHA1_Update(&OuterContext, InnerSHA, SHA_DIGEST_LENGTH);

        SHA1_Final(OuterSHA, &OuterContext);
    }

    memcpy(HMAC, OuterSHA, SHA_DIGEST_LENGTH);

    return SHA_DIGEST_LENGTH;
}

int TruncateHMAC(const uint8_t* HMAC, size_t Digits)
{
    // Take the lower four bits of the last byte.
    int Offset = (HMAC[SHA1_DIGEST_SIZE - 1] & 0x0f);

    // Starting from the offset, take the successive 4 bytes,
    // while stripping the topmost bit to prevent it being handled as a signed integer.
    int BinaryCode = 
        ((HMAC[Offset + 0] & 0x7f) << 24)
      | ((HMAC[Offset + 1] & 0xff) << 16)
      | ((HMAC[Offset + 2] & 0xff) << 8)
      | ((HMAC[Offset + 3] & 0xff))
      ;

    size_t SafeDigits = (Digits > 10)
        ? 10
        : Digits
        ;
    // Cut of excess digits, depending on desired length.
    int TruncadedHMAC = BinaryCode % DIGITS_POWER[SafeDigits];
    return TruncadedHMAC;
}
