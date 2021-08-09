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

#include "otp.h"

#include "hmac.h"
#include "timing.h"
#include "misc.h"
#include "key.h"
#include <baseencode.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SET_CHECKED(Pointer, Value) \
{ if (NULL != Pointer) *Pointer = Value; }

const char* GetErrorName(otp_error_t State)
{
    switch(State)
    {
    case OTP_SUCCESS:
        return "SUCCESS";
        break;
    case OTP_KEY_NULL:
        return "KEY IS NULL";
        break;
    case OTP_KEY_LENGTH_INVALID:
        return "KEY LENGTH IS NOT 32";
        break;
    case OTP_KEY_DECODE_ERROR:
        return "KEY COULD NOT BE DECODED FROM BASE32";
        break;
    case OTP_DIGITS_INVALID:
        return "DIGITS WAS NOT BETWEEN 3 AND 10";
        break;
    case OTP_HMAC_ERROR:
        return "HMAC CREATION FAILED";
        break;        
    }

    return "UNKNOWN ERROR";
}

int CalculateHOTP(const char* Key, int64_t Counter, size_t Digits, otp_error_t* State)
{
    if (NULL == Key)
    {
        SET_CHECKED(State, OTP_KEY_NULL);
        return -1;
    }

    size_t KeyLength = strlen(Key);
    if (32 != KeyLength)
    {
        SET_CHECKED(State, OTP_KEY_LENGTH_INVALID);
        return -1;
    }

    if (3 > Digits && 10 < Digits)
    {
        SET_CHECKED(State, OTP_KEY_DECODE_ERROR);
        return -1;
    }

    baseencode_error_t err;
    uint8_t* SecretHMAC = base32_decode (Key, KeyLength + 1, &err);
    if (NULL == SecretHMAC)
    {
        SET_CHECKED(State, OTP_DIGITS_INVALID);
        return -1;
    }

    /*size_t SecretLengthHMAC = (size_t)((KeyLength + 1.6 - 1) / 1.6);*/
    size_t SecretLengthHMAC = strlen((char*)SecretHMAC);
    
    // Convert long integer into byte array (reverse byte order).
    uint8_t DataAsReversedByteArray[sizeof(Counter)];
    ToByteArray(DataAsReversedByteArray, Counter);

    // Actually create the HMAC.
    int HOTP;
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
            HOTP = -1;
            SET_CHECKED(State, OTP_HMAC_ERROR);
        }
        else
        {
            // Cut of excess digits.
            HOTP = TruncateHMAC(HMAC, Digits);
            SET_CHECKED(State, OTP_SUCCESS);
        }
    }

    return HOTP;
}

int VerifyHOTP(int64_t HTOP, const char* Key, int64_t Counter, size_t Digits,  otp_error_t* State)
{
    int ExpectedHOTP = CalculateHOTP(Key, Counter, Digits, State);
    return ExpectedHOTP == HTOP;
}

int CalculateTOTP(const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits, otp_error_t* State)
{
    int64_t Period = Timestamp / Interval;
    int TOTP = CalculateHOTP(Key, Period, Digits, State);
    return TOTP;
}

int VerifyTOTP(int64_t TOTP, const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits,  otp_error_t* State)
{
    int ExpectedTOTP = CalculateTOTP(Key, Timestamp, Interval, Digits, State);
    return ExpectedTOTP == TOTP;
}

char* MakeStringFromOTP(int64_t HTOP, size_t Digits)
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