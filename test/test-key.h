

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
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

    const char* Expected = "35323039333238393235";

    char* Secret = GenerateSecret();
    Assert(0, "GenerateSecret", TESTLY_EXIT_ON_FAIL, Expected, Secret,
        "Expected %s, got %s.", Expected, Secret
    );

    free(Secret);
}

void TestGenerateKeyFromSecret()
{
    const char* Secret = "DEADCAFEBABE13372DEF";
    const char* Expected = "IRCUCRCDIFDEKQSBIJCTCMZTG4ZEIRKG";

    char* Key = GenerateKeyFromSecret(Secret);
    Assert(0, "GenerateKeyFromSecret", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    free(Key);
}

void TestGenerateKey()
{
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

    const char* Expected = "GM2TGMRTGAZTSMZTGMZDGOBTHEZTEMZV";
       
    char* Key = GenerateKey();
    Assert(0, "GenerateKeyFromSecret", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );

    free(Key);
}