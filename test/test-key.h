

/// key.h

void TestNormalizeKey()
{
    const char* KeyReference = "HELLO";
    const char* Expected = "HELLO===========================";

    char* Key = strdup(KeyReference);
    NormalizeKey(&Key);
    Assert(0, "NormalizeKey", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    free(Key);
}

void TestGenerateSecretFromSeed()
{
    const char* Seed = "0001337000";
    const char* Expected = "30303031333337303030";

    char* SeededSecret = GenerateSecretFromSeed(Seed);
    Assert(0, "GenerateSecretFromSeed", TESTLY_EXIT_ON_FAIL, Expected, SeededSecret,
        "Got %s from seed %s.", SeededSecret, Seed
    );
    free(SeededSecret);
}

void TestGenerateSecret()
{
    Fail("TestGenerateSecret", TESTLY_EXIT_ON_FAIL, "Not implemented yet!");
}

void TestGenerateKeyFromSecret()
{
    /*const char* Secret = "CAFEBABECAFEBABECAFE";*/
    const char* Secret = "00000000000000000000";
    const char* Expected = "GAYDAMBQGAYDAMBQGAYDAMBQGAYDAMBQ";

    char* Key = GenerateKeyFromSecret(Secret);
    Assert(0, "GenerateKeyFromSecret", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    free(Key);
}

void TestGenerateKey()
{
    Fail("TestGenerateKey", TESTLY_EXIT_ON_FAIL, "Not implemented yet!");
}