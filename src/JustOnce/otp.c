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

#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sha/sha.h>
#include <baseencode/baseencode.h>
#include "hmac.h"
#include "timing.h"
#include "misc.h"

void ToByteArray(uint8_t* ByteArray, int64_t Data);


const char* CheckForError(int HMAC)
{
    if (0 < HMAC)
    {
        return "SUCCESS";
    }

    switch(HMAC)
    {
    case -1:
        return "INVALID KEY POINTER";
        break;
    case -2:
        return "INVALID KEY LENGTH";
        break;
    case -3:
        return "INVALID DIGIT LENGTH";
        break;
    case -4:
        return "INVALID KEY ENCODING";
        break;
    }

    return "UNKNOWN ERROR";
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

        char* NewKey = malloc(RequiredKeyLength + 1);
        strcat(NewKey, *Key);
        strcat(NewKey, Appendix);
        NewKey[RequiredKeyLength] = '\0';

        free(*Key);
        *Key = NewKey;
    }
    else if (0 > MissingKeyCharacters)
    {        
        char* NewKey = malloc(RequiredKeyLength + 1);
        strncpy(NewKey, *Key, RequiredKeyLength);
        NewKey[RequiredKeyLength] = '\0';

        free(*Key);
        *Key = NewKey;
    }

    ToUpperCase(Key);
}

int CalculateHOTP (const char* Key, int64_t Data, size_t Digits)
{
    if (NULL == Key)
    {
        return -1;
    }

    size_t KeyLength = strlen(Key);
    if (32 != KeyLength)
    {
        return -2;
    }

    if (3 > Digits && 10 < Digits)
    {
        return -3;
    }

    baseencode_error_t err;
    uint8_t* SecretHMAC = base32_decode (Key, KeyLength + 1, &err);
    if (NULL == SecretHMAC)
    {
        return -4;
    }

    /*size_t SecretLengthHMAC = (size_t)((KeyLength + 1.6 - 1) / 1.6);*/
    size_t SecretLengthHMAC = strlen((char*)SecretHMAC);
    
    // Convert long integer into byte array (reverse byte order).
    uint8_t DataAsReversedByteArray[sizeof(Data)];
    ToByteArray(DataAsReversedByteArray, Data);

    // Actually create the HMAC.
    int TruncadedHMAC;
    {
        unsigned char HMAC[SHA1_DIGEST_SIZE];
        size_t ActualHMACLength = CreateHMAC(HMAC,
            SecretHMAC,
            SecretLengthHMAC,
            DataAsReversedByteArray,
            sizeof(DataAsReversedByteArray)
        );

        free(SecretHMAC);

        if (SHA1_DIGEST_SIZE != ActualHMACLength)
        {
            // Indicate size error.
            TruncadedHMAC = -6;
        }
        else
        {
            // Cut of excess digits.
            TruncadedHMAC = TruncateHMAC(HMAC, Digits);            
        }
    }

    return TruncadedHMAC;
}

int VerifyHOTP(int64_t HTOP, const char* Key, int64_t Data, size_t Digits)
{
    int64_t ExpectedHTOP = CalculateHOTP(Key, Data, Digits);    
    return ExpectedHTOP == HTOP;
}

char* MakeStringFromHOTP(int64_t HTOP, size_t Digits)
{
    char FMT[7];
    snprintf(FMT, 7, (10 > Digits) ? "%%00%zuzu" : "%%0%zuzu", Digits);

    char* Buffer = malloc(Digits + 1);
    snprintf(Buffer, Digits + 1, FMT, HTOP);

    return Buffer;
}

//

void ToByteArray(uint8_t* ByteArray, int64_t Data)
{
    static const size_t DataSize = sizeof(Data);

    uint8_t* RawData = (uint8_t*)&Data;
    for (size_t DataIndex = 0, ByteArrayIndex = DataSize - 1
       ; DataIndex < DataSize && 0 <= ByteArrayIndex
       ; DataIndex++, ByteArrayIndex--)
    {
        uint8_t Value = RawData[DataIndex];
        ByteArray[ByteArrayIndex] = Value;
    }
}