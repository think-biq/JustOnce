

// otp.h

int TestToByteArray()
{
    int64_t Thingy = -1;
    uint8_t Buffer[sizeof(int64_t)];
    uint8_t Expected[sizeof(int64_t)] = {
        255, 255, 255, 255, 255, 255, 255, 255
    };

    ToByteArray(Buffer, Thingy);
    return Assert(sizeof(Buffer), "TestToByteArray", TESTLY_EXIT_ON_FAIL, Expected, Buffer,
        "Expected %s, got %s.", Expected, Buffer
    );    
}

int TestCalculateHOTP()
{
    const char* Key = "HELLO===========================";
    const int ExpectedCodes[8] = {
        647, 7647, 27647, 227647, 6227647, 76227647, 976227647, 976227647
    };

    int Passed;
    for (size_t Index = 0; Index < 8; ++Index)
    {
        int Expected = ExpectedCodes[Index];
        int Digits = 3 + Index;

        char Name[17];
        sprintf(Name, "CalculateHOTP@%02i", Digits);

        otp_error_t State;
        int HOTP = CalculateHOTP(Key, 0, Digits, &State);
        if (VERBOSE) printf("%s finished with: %s\n", Name, GetErrorName(State));
        Passed = Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &HOTP,
            "Expected %i, got %i.", Expected, HOTP
        );
        if (0 == Passed) break;
    }

    return Passed;
}

int TestVerifyHOTP()
{
    const char* Key = "HELLO===========================";
    const int ExpectedCodes[8] = {
        647, 7647, 27647, 227647, 6227647, 76227647, 976227647, 976227647
    };
    int Passed;

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
        Passed = Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &Verified,
            "Expected %i, got %i.", Expected, Verified
        );
        if (0 == Passed) break;
    }

    return Passed;
}

int TestCalculateTOTP()
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
    return Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &TOTP,
        "Expected %i, got %i.", Expected, TOTP
    );
}

int TestVerifyTOTP()
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
    return Assert(sizeof(int), Name, TESTLY_EXIT_ON_FAIL, &Expected, &bVerfied,
        "Expected %i, got %i.", Expected, bVerfied
    );
}

int TestMakeStringFromOTP()
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

    int Passed;
    for (size_t Index = 0; Index < 8; ++Index)
    {
        const char* Expected = ExpectedCodes[Index];
        int Digits = 3 + Index;
        int OTP = 1;

        char* Code = MakeStringFromOTP(OTP, Digits);
        Passed = Assert(0, "MakeStringFromHOTP", TESTLY_EXIT_ON_FAIL, Expected, Code,
            "Expected %s, got %s.", Expected, Code
        );

        free(Code);

        if (0 == Passed) break;
    }

    return Passed;
}

int TestGenerateAuthURL()
{
    const otp_operation_t Type = OTP_OP_TOTP;
    const char* AccountName = "support@think-biq.com";
    const char* Issuer = "biq";
    const size_t Digits = 6;
    const size_t Interval = 30;
    const char* Key = "???";

    char* EncodedAccountName = URLEncode(AccountName);
    char* EncodedIssuer =  URLEncode(Issuer);

    const char Expected[JUSTONCE_OTP_URL_MAX_LENGTH];
    snprintf((char*)Expected, JUSTONCE_OTP_URL_MAX_LENGTH, JUSTONCE_OTP_URL_FMT,
        "totp", EncodedAccountName, Key, EncodedIssuer, Digits, Interval);

    free(EncodedIssuer);
    free(EncodedAccountName);

    char* AuthURI = GenerateAuthURI(Type, Key, AccountName, Issuer, Digits, Interval);
    int Passed = Assert(0, "GenerateAuthURI", TESTLY_EXIT_ON_FAIL, Expected, AuthURI,
        "Expected %s, got %s.", Expected, AuthURI
    );

    free(AuthURI);

    return Passed;
}