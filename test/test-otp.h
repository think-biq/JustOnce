

// otp.h

void TestToByteArray()
{
    int64_t Thingy = -1;
    uint8_t Buffer[sizeof(int64_t)];
    uint8_t Expected[sizeof(int64_t)] = {
        255, 255, 255, 255, 255, 255, 255, 255
    };

    ToByteArray(Buffer, Thingy);
    Assert(sizeof(Buffer), "TestToByteArray", TESTLY_EXIT_ON_FAIL, Expected, Buffer,
        "Expected %s, got %s.", Expected, Buffer
    );    
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

        char Name[17];
        sprintf(Name, "CalculateHOTP@%02i", Digits);

        int HOTP = CalculateHOTP(Key, 0, Digits);
        Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &HOTP,
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

        char Name[14];
        sprintf(Name, "VerifyHOTP@%02i", Digits);

        int Verified = VerifyHOTP(HOTP, Key, 0, Digits);
        Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &Verified,
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
        Assert(0, "MakeStringFromHOTP", TESTLY_EXIT_ON_FAIL, Expected, Code,
            "Expected %s, got %s.", Expected, Code
        );

        free(Code);
    }
}