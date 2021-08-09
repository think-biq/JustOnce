

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

void TestGenerateSecretEntropy()
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

    Assert(sizeof(int), "FoundCollision", TESTLY_EXIT_ON_FAIL, &Expected, &CollisionIndex,
        "Had collision on %i. generation.", CollisionIndex
    );
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