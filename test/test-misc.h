

// misc.h

int TestUpperCase()
{
    const char* LowerCase = "lower case 42!";
    const char* Expected = "LOWER CASE 42!";
    
    int Passed = 1;

    // Test MakeUpperCase
    {
        char* UpperCase = MakeUpperCase(LowerCase);
        Passed &= Check("MakeUpperCase", 0, Expected, UpperCase,
            "Expected (%s), got (%s).", Expected, UpperCase
        );
        free(UpperCase);
        if (0 == Passed) return Passed;
    }

    // Test ToUpperCase
    {
        char* LowerCaseDup = strdup(LowerCase);
        ToUpperCase(&LowerCaseDup);
        Passed &= Check("ToUpperCase", 0, Expected, LowerCaseDup,
            "Expected %s, got %s.", Expected, LowerCaseDup
        );
        free(LowerCaseDup);
        if (0 == Passed) return Passed;
    }

    return Passed;
}

int TestHexify()
{
    uint8_t Buffer[5] = {
        202, 254, 186, 190, 105
    };
    const char* Expected = "cafebabe69";

    char* Hash = Hexify(Buffer, 5);
    int Passed = Check("Hexify", 0, Expected, Hash,
        "Expected %s, got %s.", Expected, Hash
    );
    free(Hash);

    return Passed;
}

int TestURLEncode()
{
    const char* Expected = "Email%3a%20hansimgl%c3%bcck%40hatkeine.email";
    char* Encoded = URLEncode("Email: hansimglück@hatkeine.email");

    int Passed = Check("URLEncode", 0, Expected, Encoded,
        "Expected %s, got %s.", Expected, Encoded
    );
    free(Encoded);

    return Passed;
}