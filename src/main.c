#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <baseencode/baseencode.h>
#include <JustOnce/otp.h>
#include <JustOnce/timing.h>
#include <JustOnce/key.h>
#include <JustOnce/misc.h>

int main (void) {
    /*const char* Secret = "";*/
    const char* Secret = "cafe";
    /*const char* Secret = "CAFE0000000000000000";*/
    /*const char* Secret = "CAFECAFECAFECAFECAFE";*/
    /*const char* Secret = "CAFECAFECAFECAFECAFECAFE";*/
    const char* Seed = "Do everthing with LOVE!";

    if (0)
    {
        char* SeededSecret = GenerateSecretFromSeed(Seed);
        printf("SeededSecret: %s, Seed: %s\n", SeededSecret, Seed);

        free(SeededSecret);
    }

    int Digits = 6;
    int Interval = 30;

    int HMAC;
    {
        char* Key;
        if (0)
        {
            char* NormalizedSecret = MakeUpperCase(Secret);
            Key = GenerateKeyFromSecret(NormalizedSecret);
            free(NormalizedSecret);
        }
        else
        {
            Key = GenerateKeyFromSeed(Seed);
        }

        if (NULL == Key)
        {
            printf("WHY?\n");
            exit(0);
        }

        printf("Generaded Key: %s (Length: %lu)\n", Key, strlen(Key));
        
        NormalizeKey(&Key);

        printf("Using Key: %s (Length: %lu)\n", Key, strlen(Key));

        int64_t TimeFrame = GetTimeFrameNow(Interval);
        HMAC = CalculateHOTP(Key, TimeFrame, Digits);
        if (0 > HMAC)
        {
            printf("Error creating HMAC: %i (%s)\n", HMAC, CheckForError(HMAC));
            return HMAC;
        }

        free(Key);
    }

    {
        char* Code;
        Code = MakeStringFromHOTP(HMAC, Digits);
        printf("%s", Code);
        free(Code);
    }

    return 0;
}