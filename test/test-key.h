

/// key.h

int TestIsValidKey()
{
    int Passed = 1;
    {
        const char* Key = "HELLO===========================";
        const int Expected = 1;

        int bIsValid = IsValidKey(Key);
        Passed &= Assert(sizeof(int), "IsValidKey@Valid", TESTLY_EXIT_ON_FAIL, &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    {
        const char* Key = "NotValid!";
        const int Expected = 0;

        int bIsValid = IsValidKey(Key);
        Passed &= Assert(sizeof(int), "IsValidKey@Invalid", TESTLY_EXIT_ON_FAIL, &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    {
        const char* Key = "HELLO===========================HELLO";
        const int Expected = 0;

        int bIsValid = IsValidKey(Key);
        Passed &= Assert(sizeof(int), "IsValidKey@TooLong", TESTLY_EXIT_ON_FAIL, &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    return Passed;
}

int TestNormalizeKey()
{
    const char* KeyReference = "HELLO";
    const char* Expected = "HELLO===========================";
    char* Key = strdup(KeyReference);

    NormalizeKey(&Key);
    int Passed = Assert(0, "NormalizeKey", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );
    
    free(Key);

    return Passed;
}

int TestGenerateSecretFromSeed()
{
    const char* Seed = "0001337000";
    const char* Expected = "30303031333337303030";

    char* SeededSecret = GenerateSecretFromSeed(Seed);
    int Passed = Assert(0, "GenerateSecretFromSeed", TESTLY_EXIT_ON_FAIL, Expected, SeededSecret,
        "Got %s from seed %s.", SeededSecret, Seed
    );

    free(SeededSecret);

    return Passed;
}

int TestGenerateSecret()
{
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

    const char* Expected = "35323039333238393235";

    char* Secret = GenerateSecret();
    int Passed = Assert(0, "GenerateSecret", TESTLY_EXIT_ON_FAIL, Expected, Secret,
        "Expected %s, got %s.", Expected, Secret
    );

    free(Secret);

    return Passed;
}

int TestGenerateSecretEntropy()
{
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(1); 
    // Resets seed to 0.
    SetRandomizerSeed(time(NULL));

    const size_t SampleSize = 2000;
    char* Collection[SampleSize];

    for (size_t Index = 0; Index < SampleSize; ++Index)
    {
        Collection[Index] = GenerateSecret();
    }

    int CollisionIndex = -1;
    for (size_t Index = 0; Index < SampleSize; ++Index)
    {
        char* Reference = Collection[Index];
        for (size_t InnerIndex = 0; InnerIndex < SampleSize; ++InnerIndex)
        {
            if (Index == InnerIndex) continue;

            char* Sample = Collection[InnerIndex];
            if (0 == strcmp(Reference, Sample))
            {
                CollisionIndex = InnerIndex;
                break;
            }
        }

        if (-1 < CollisionIndex)
        {
            break;
        }
    }

    for (size_t Index = 0; Index < SampleSize; ++Index)
    {
        free(Collection[Index]);
    }

    int Expected = -1;

    return Assert(sizeof(int), "FoundCollision", TESTLY_EXIT_ON_FAIL, &Expected, &CollisionIndex,
        "Had collision on %i. generation. (Very rare case)", CollisionIndex
    );
}

int TestGenerateKeyFromSecret()
{
    const char* Secret = "DEADCAFEBABE13372DEF";
    const char* Expected = "IRCUCRCDIFDEKQSBIJCTCMZTG4ZEIRKG";

    char* Key = GenerateKeyFromSecret(Secret);
    int Passed = Assert(0, "GenerateKeyFromSecret", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );

    free(Key);

    return Passed;
}

int TestGenerateKey()
{
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

    const char* Expected = "GM2TGMRTGAZTSMZTGMZDGOBTHEZTEMZV";
       
    char* Key = GenerateKey();
    int Passed = Assert(0, "GenerateKeyFromSecret", TESTLY_EXIT_ON_FAIL, Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );

    free(Key);

    return Passed;
}