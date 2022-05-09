
enum TestKeyConstants {
    TestKey_SampleSize = 1000
};

/// key.h

int TestIsValidKey()
{
    int Passed = 1;
    {
        const char* Key = "HELLO===========================";
        const int Expected = 1;

        int bIsValid = IsValidKey(Key);
        Passed &= Check("IsValidKey@Valid", sizeof(int),
            &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    {
        const char* Key = "NotValid!";
        const int Expected = 0;

        int bIsValid = IsValidKey(Key);
        Passed &= Check("IsValidKey@Invalid", sizeof(int),
            &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    {
        const char* Key = "HELLO===========================HELLO";
        const int Expected = 0;

        int bIsValid = IsValidKey(Key);
        Passed &= Check("IsValidKey@TooLong", sizeof(int),
            &Expected, &bIsValid,
            "Expected %d, got %d.", Expected, bIsValid
        );
    }

    return Passed;
}

int TestNormalizeKey()
{
    const char* Key = "HELLO";
    const char* Expected = "HELLO===========================";

    char* NormalizedKey = NormalizeKey(Key);
    int Passed = Check("NormalizeKey", 0,
        Expected, NormalizedKey,
        "Expected %s, got %s.", Expected, NormalizedKey
    );
    
    free(NormalizedKey);

    return Passed;
}

int TestGenerateSecretFromSeed()
{
    const char* Seed = "0001337000";
    const char* Expected = "30303031333337303030";

    char* SeededSecret = GenerateSecretFromSeed((uint8_t*)Seed, strlen(Seed));
    int Passed = Check("GenerateSecretFromSeed", 0,
        Expected, SeededSecret,
        "Got %s from seed %s.", SeededSecret, Seed
    );

    free(SeededSecret);

    return Passed;
}

int TestGenerateSecret()
{
    int bIsSafe = GetRandomizerSafe();
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

#if defined(_WIN32)
    const char* Expected = "2627F6859715AD1DD294";
#else
    const char* Expected = "42FB9FE059815A8166A1";
#endif

    char* Secret = GenerateSecret();
    int Passed = Check("GenerateSecret", 0,
        Expected, Secret,
        "Expected %s, got %s.", Expected, Secret
    );

    free(Secret);

    // Reset randomizer safe state.
    SetRandomizerSafe(bIsSafe);

    return Passed;
}

int TestGenerateSecretEntropy()
{
    int bIsSafe = GetRandomizerSafe();
    // Activates crypto safe rand.
    SetRandomizerSafe(1); 
    // Resets seed to current time.
    SetRandomizerSeed(time(NULL));

    char* Collection[TestKey_SampleSize];

    for (size_t Index = 0; Index < TestKey_SampleSize; ++Index)
    {
        char* Secret = GenerateSecret();
        if (NULL == Secret)
        {
            char Msg[64];
            snprintf(Msg, 64, "Could not generate secret sample %zu!", Index);
            Fail("GenerateSecrets", 1, Msg);
        }

        Collection[Index] = Secret;
    }

    SetRandomizerSafe(bIsSafe);

    int CollisionIndex = -1;
    for (size_t Index = 0; Index < TestKey_SampleSize; ++Index)
    {
        char* Reference = Collection[Index];
        for (size_t InnerIndex = 0; InnerIndex < TestKey_SampleSize; ++InnerIndex)
        {
            if (Index == InnerIndex) continue;

            char* Sample = Collection[InnerIndex];
            if (0 == strcmp(Reference, Sample))
            {
                printf("Collision detected! (%zu == %zu)\n", Index, InnerIndex);
                CollisionIndex = InnerIndex;
                break;
            }
        }

        if (-1 < CollisionIndex)
        {
            break;
        }
    }

    for (size_t Index = 0; Index < TestKey_SampleSize; ++Index)
    {
        free(Collection[Index]);
    }

    int Expected = -1;

    return Check("FoundCollision", sizeof(int),
        &Expected, &CollisionIndex,
        "Had collision on %i. generation. (Very rare case)", CollisionIndex
    );
}

int TestGenerateKeyFromSecret()
{
    const char* Secret = "DEADCAFEBABE13372DEF";
    const char* Expected = "IRCUCRCDIFDEKQSBIJCTCMZTG4ZEIRKG";

    char* Key = GenerateKeyFromSecret(Secret);
    int Passed = Check("GenerateKeyFromSecret", 0,
        Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );

    free(Key);

    return Passed;
}

int TestGenerateKey()
{
    int bIsSafe = GetRandomizerSafe();
    // Deactivates crypto safe rand (to be deterministic for tests).
    SetRandomizerSafe(0); 
    // Resets seed to 0.
    SetRandomizerSeed(0);

#if defined(_WIN32)
    const char* Expected = "GI3DEN2GGY4DKOJXGE2UCRBRIRCDEOJU";
#else
    const char* Expected = "GQZEMQRZIZCTANJZHAYTKQJYGE3DMQJR";
#endif

    char* Key = GenerateKey();
    int Passed = Check("GenerateKey", 0,
        Expected, Key,
        "Expected %s, got %s.", Expected, Key
    );

    free(Key);

    SetRandomizerSafe(bIsSafe);

    return Passed;
}