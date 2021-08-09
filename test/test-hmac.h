

#include <JustOnce/hmac.h>
#include <sha/sha.h>

/// hmac.h

int TestTruncateHMAC()
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

    int Passed;
    for (size_t Index = 0; Index < 11; ++Index)
    {
        int Expected = ExpectedHMACs[Index];
        int TruncadedHMAC = TruncateHMAC(Buffer, Index);
        Passed = Assert(sizeof(int), "TruncateHMAC", TESTLY_EXIT_ON_FAIL, &Expected, &TruncadedHMAC,
            "For %zu digits, expected (%i), got (%i).", Index, Expected, TruncadedHMAC
        );
        if (0 == Passed) break;
    }

    return Passed;
}

int TestCreateHMAC()
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

    return Assert(SHA_DIGEST_LENGTH, "CreateHMAC", TESTLY_EXIT_ON_FAIL, Buffer, Expected,
        "Expected (%s), got (%s).", Expected, Buffer
    );
}