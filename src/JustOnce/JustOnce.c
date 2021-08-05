//
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sha/sha.h>
#include <hmac/hmac.h>
#include <baseencode/baseencode.h>

static int64_t DIGITS_POWER[] = { 
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000
};

void ToByteArray(uint8_t* ByteArray, size_t DataSize, int64_t Data) {
    uint8_t* RawData = (uint8_t*)&Data;
    for (size_t DataIndex = 0, ByteArrayIndex = DataSize - 1
       ; DataIndex < DataSize && 0 <= ByteArrayIndex
       ; DataIndex++, ByteArrayIndex--) {
        uint8_t Value = RawData[DataIndex];
        ByteArray[ByteArrayIndex] = Value;
    }
}

int TruncateHMAC(unsigned const char* HMAC, size_t Digits) {
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

    // Cut of excess digits, depending on desired length.
    int TruncadedHMAC = BinaryCode % DIGITS_POWER[Digits];
    return TruncadedHMAC;
}

int64_t GetUnixTimeNow() {
	return (int64_t)time(NULL);
}

int64_t GetTimeFrame(int64_t UnixTime, size_t Interval) {
    return UnixTime / (int64_t)Interval;    
}

int64_t GetTimeFrameNow(size_t Interval) {
	return GetTimeFrame(GetUnixTimeNow(), Interval);
}

int CalculateHOTP (const char* Key, int64_t Data, size_t Digits) {
    static const size_t DataSize = sizeof(Data);

    if (NULL == Key) {
        return -1;
    }

    if (3 > Digits && 10 < Digits) {
        return -2;
    }

    size_t KeyLength = strlen(Key);
    if (32 != KeyLength) {
        return -3;
    }

    baseencode_error_t err;
    uint8_t* SecretHMAC = base32_decode(Key, KeyLength + 1, &err);
    if (NULL == SecretHMAC) {
        return -4;
    }

    //size_t SecretLengthHMAC = (size_t)((KeyLength + 1.6 - 1) / 1.6);
    size_t SecretLengthHMAC = strlen((char*)SecretHMAC);
    if (20 != SecretLengthHMAC) {
        return -5;
    }
    
    // Convert long integer into byte array (reverse byte order).
    uint8_t DataAsReversedByteArray[DataSize];//{ 0, 0, 0, 0, 0, 0, 0, 0 };
    ToByteArray(DataAsReversedByteArray, DataSize, Data);

    // Actually create the HMAC.
    unsigned char HMAC[SHA1_DIGEST_SIZE];
    {
        size_t ActualHMACLength = -1;
        CreateSHA1HMAC(
            SecretHMAC,
            SecretLengthHMAC,
            DataAsReversedByteArray,
            sizeof(DataAsReversedByteArray),
            HMAC,
            &ActualHMACLength
        );
    }

    free(SecretHMAC);

    // Cut of excess digits.
    int TruncadedHMAC = TruncateHMAC(HMAC, Digits);
    return TruncadedHMAC;
}

char* MakeStringFromHOTP(int64_t Hash, size_t Digits) {
    char FMT[7];
    snprintf(FMT, 7, (10 > Digits) ? "%%00%zuzu" : "%%0%zuzu", Digits);

    char* Buffer = malloc(Digits + 1);
    snprintf(Buffer, Digits + 1, FMT, Hash);

    return Buffer;
}