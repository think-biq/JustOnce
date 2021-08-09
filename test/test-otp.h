

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

        otp_error_t State;
        int HOTP = CalculateHOTP(Key, 0, Digits, &State);
        if (VERBOSE) printf("%s finished with: %s\n", Name, GetErrorName(State));
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

        otp_error_t State;
        int Verified = VerifyHOTP(HOTP, Key, 0, Digits, &State);
        if (VERBOSE) printf("%s finished with: %s\n", Name, GetErrorName(State));
        Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &Verified,
            "Expected %i, got %i.", Expected, Verified
        );
    }
}

void TestCalculateTOTP()
{
    const char* Key = "GNUSLASHLINUX===================";
    int Expected = 498977;
    int Digits = 6;
    int64_t Timestamp = 433512000;
    int64_t Interval = 30;
    const char* Name = "CalculateTOTP@06";

    otp_error_t State;
    int TOTP = CalculateTOTP(Key, Timestamp, Interval, Digits, &State);
    if (VERBOSE) printf("%s finished with: %s\n", Name, GetErrorName(State));
    Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &TOTP,
        "Expected %i, got %i.", Expected, TOTP
    );
}

void TestVerifyTOTP()
{
    const char* Key = "GNUSLASHLINUX===================";  
    int TOTP = 498977;
    int Digits = 6;
    int64_t Timestamp = 433512000;
    int64_t Interval = 30;
    const char* Name = "VerifyTOTP@06";
    int Expected = 1;

    otp_error_t State;
    int bVerfied = VerifyTOTP(TOTP, Key, Timestamp, Interval, Digits, &State);
    if (VERBOSE) printf("%s finished with: %s\n", Name, GetErrorName(State));
    Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &bVerfied,
        "Expected %i, got %i.", Expected, bVerfied
    );
}

void TestMakeStringFromOTP()
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
        int OTP = 1;

        char* Code = MakeStringFromOTP(OTP, Digits);
        Assert(0, "MakeStringFromHOTP", TESTLY_EXIT_ON_FAIL, Expected, Code,
            "Expected %s, got %s.", Expected, Code
        );

        free(Code);
    }
}