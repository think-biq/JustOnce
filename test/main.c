#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <baseencode/baseencode.h>
#include <JustOnce/otp.h>
#include <JustOnce/timing.h>
#include <JustOnce/key.h>
#include <JustOnce/misc.h>
#include <JustOnce/hmac.h>
#include <sha/sha.h>

#include "testly.h"

#define VERBOSE 0

void TestHexify()
{
    uint8_t Buffer[5] = {
        202, 254, 186, 190, 105
    };
    const char* Expected = "cafebabe69";

    char* Hash = Hexify(Buffer, 5);
    Assert(0, "Hexify", Expected, Hash,
        "Expected %s, got %s.", Expected, Hash
    );
    free(Hash);
}

void TestGenerateSecretFromSeed()
{
    const char* Seed = "0001337000";
    const char* Expected = "30303031333337303030";

    char* SeededSecret = GenerateSecretFromSeed(Seed);
    Assert(0, "GenerateSecretFromSeed", Expected, SeededSecret,
        "Got %s from seed %s.", SeededSecret, Seed
    );
    free(SeededSecret);
}

void TestUpperCase()
{
    const char* LowerCase = "lower case 42!";
    const char* Expected = "LOWER CASE 42!";

    // Test MakeUpperCase
    {
        char* UpperCase = MakeUpperCase(LowerCase);
        Assert(0, "MakeUpperCase", Expected, UpperCase,
            "Expected (%s), got (%s).", Expected, UpperCase
        );
        free(UpperCase);
    }

    // Test ToUpperCase
    {
        char* LowerCaseDup = strdup(LowerCase);
        ToUpperCase(&LowerCaseDup);
        Assert(0, "ToUpperCase", Expected, LowerCaseDup,
            "Expected %s, got %s.", Expected, LowerCaseDup
        );
        free(LowerCaseDup);
    }
}

void TestGenerateKeyFromSecret()
{
    /*const char* Secret = "CAFEBABECAFEBABECAFE";*/
    const char* Secret = "00000000000000000000";
    const char* Expected = "GAYDAMBQGAYDAMBQGAYDAMBQGAYDAMBQ";

    char* Key = GenerateKeyFromSecret(Secret);
    Assert(0, "GenerateKeyFromSecret", Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    free(Key);
}

void TestNormalizeKey()
{
    const char* KeyReference = "HELLO";
    const char* Expected = "HELLO===========================";

    char* Key = strdup(KeyReference);
    NormalizeKey(&Key);
    Assert(0, "NormalizeKey", Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    free(Key);
}

void TestCalculateHOTP()
{
    const char* Key = "HELLO===========================";
    const int ExpectedCodes[8] = {
        647, 7647, 27647, 227647, 6227647, 76227647, 976227647, 976227647
    };

    for (size_t Index = 0; Index < 8; ++Index)
    {
        int Expected = ExpectedCodes[Index];
        int Digits = 3 + Index;
        int HOTP = CalculateHOTP(Key, 0, Digits);
        char Name[17];
        sprintf(Name, "CalculateHOTP@%02i", Digits);
        Assert(sizeof(int), Name, &Expected, &HOTP,
            "Expected %i, got %i.", Expected, HOTP
        );
    }
}

void TestVerifyHOTP()
{
    const char* Key = "HELLO===========================";
    const int ExpectedCodes[8] = {
        647, 7647, 27647, 227647, 6227647, 76227647, 976227647, 976227647
    };

    int Expected = 1;
    for (size_t Index = 0; Index < 8; ++Index)
    {
        int HOTP = ExpectedCodes[Index];
        int Digits = 3 + Index;
        int Verified = VerifyHOTP(HOTP, Key, 0, Digits);
        char Name[14];
        sprintf(Name, "VerifyHOTP@%02i", Digits);
        Assert(sizeof(int), Name, &Expected, &Verified,
            "Expected %i, got %i.", Expected, Verified
        );
    }
}

void TestMakeStringFromHOTP()
{
    const char* ExpectedCodes[8] = {
        "001", 
        "0001", 
        "00001", 
        "000001", 
        "0000001", 
        "00000001",
        "000000001",
        "0000000001"
    };

    for (size_t Index = 0; Index < 8; ++Index)
    {
        const char* Expected = ExpectedCodes[Index];
        int Digits = 3 + Index;
        int HMAC = 1;
        char* Code = MakeStringFromHOTP(HMAC, Digits);
        Assert(0, "MakeStringFromHOTP", Expected, Code,
            "Expected %s, got %s.", Expected, Code
        );
        free(Code);
    }
}

void TestTiming()
{
    {
        int64_t ExpectedTime = (int64_t)time(NULL);
        int64_t UnixTime = GetUnixTimeNow();
        Assert(sizeof(int), "GetUnixTimeNow", &ExpectedTime, &UnixTime,
            "Expected %i, got %i.", ExpectedTime, UnixTime
        );

        int64_t ExpectedTimeFrame = ExpectedTime / 30;
        int64_t TimeFrame = GetTimeFrameNow(30);
         Assert(sizeof(int), "GetTimeFrameNow", &ExpectedTimeFrame, &TimeFrame,
            "Expected %i, got %i.", ExpectedTimeFrame, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(30, 30);
        Assert(sizeof(int), "GetTimeFrame@30:30", &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(59, 30);
        Assert(sizeof(int), "GetTimeFrame@59:30", &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 2;
        int64_t TimeFrame = GetTimeFrame(60, 30);
        Assert(sizeof(int), "GetTimeFrame@60:30", &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }
}

void TestTruncateHMAC()
{
    uint8_t Buffer[SHA_DIGEST_LENGTH];
    memset(Buffer, 255, SHA_DIGEST_LENGTH);
    int ExpectedHMACs[11] = {
                 0,
                 7,
                47,
               647,
              3647,
             83647,
            483647,
           7483647,
          47483647,
         147483647,
        2147483647
    };

    for (size_t Index = 0; Index < 11; ++Index)
    {
        int Expected = ExpectedHMACs[Index];
        int TruncadedHMAC = TruncateHMAC(Buffer, Index);
        Assert(sizeof(int), "TruncateHMAC", &Expected, &TruncadedHMAC,
            "For %zu digits, expected (%i), got (%i).", Index, Expected, TruncadedHMAC
        );        
    }
}

void TestCreateHMAC()
{
    uint8_t Expected[SHA_DIGEST_LENGTH] = {
        42,187,41,28,118,241,248,132,48,53,243,129,8,171,201,242,197,9,161,43
    };
    uint8_t Buffer[SHA_DIGEST_LENGTH];
    memset(Buffer, 0, SHA_DIGEST_LENGTH);
    uint8_t Data[8];
    memset(Data, 69, 8);
    const char* Secret = "CAFEBABECAFEBABEDEAD";

    int State = CreateHMAC(Buffer,
        (const uint8_t*)Secret, strlen(Secret),
        Data, sizeof(Data)
    );

    if (VERBOSE)
    {
        char* Hex = Hexify(Buffer, SHA_DIGEST_LENGTH);
        printf("Hex(Buffer): (%s)\n", Hex);
        free(Hex);
    }

    if (VERBOSE)
    {
        char* Hex = Hexify(Expected, SHA_DIGEST_LENGTH);
        printf("Hex(Expected): (%s)\n", Hex);
        free(Hex);
    }

    Assert(SHA_DIGEST_LENGTH, "CreateHMAC", Buffer, Expected,
        "Expected (%s), got (%s).", Expected, Buffer
    );
}

int main (void)
{
    RUN_TEST(TestHexify);
    RUN_TEST(TestGenerateSecretFromSeed);
    RUN_TEST(TestUpperCase);
    RUN_TEST(TestGenerateKeyFromSecret);
    RUN_TEST(TestNormalizeKey);
    RUN_TEST(TestCalculateHOTP);
    RUN_TEST(TestVerifyHOTP);
    RUN_TEST(TestMakeStringFromHOTP);
    RUN_TEST(TestTiming);    
    RUN_TEST(TestCreateHMAC);
    RUN_TEST(TestTruncateHMAC);

    return 0;
}