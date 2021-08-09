

// misc.h

int TestUpperCase()
{
    const char* LowerCase = "lower case 42!";
    const char* Expected = "LOWER CASE 42!";
    
    int Passed;

    // Test MakeUpperCase
    {
        char* UpperCase = MakeUpperCase(LowerCase);
        Passed = Assert(0, "MakeUpperCase", TESTLY_EXIT_ON_FAIL, Expected, UpperCase,
            "Expected (%s), got (%s).", Expected, UpperCase
        );
        free(UpperCase);
        if (0 == Passed) return Passed;
    }

    // Test ToUpperCase
    {
        char* LowerCaseDup = strdup(LowerCase);
        ToUpperCase(&LowerCaseDup);
        Assert(0, "ToUpperCase", TESTLY_EXIT_ON_FAIL, Expected, LowerCaseDup,
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
    int Passed = Assert(0, "Hexify", TESTLY_EXIT_ON_FAIL, Expected, Hash,
        "Expected %s, got %s.", Expected, Hash
    );
    free(Hash);

    return Passed;
}