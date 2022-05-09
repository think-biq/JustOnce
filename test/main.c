
#undef TESTLY_ASSERT_DISABLED
#include <testly/assert.h>
#include <testly/run.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>

#include <JustOnce/otp.h>
#include <JustOnce/timing.h>
#include <JustOnce/key.h>
#include <JustOnce/misc.h>

#include <ShaOne/hash.h>
#include <carter/randolph.h>

#define VERBOSE 0

#include "test-hmac.h"
#include "test-key.h"
#include "test-misc.h"
#include "test-otp.h"
#include "test-timing.h"

int TestRandom()
{

    int bIsSafe = GetRandomizerSafe();
    SetRandomizerSafe(1);

    int Result = 0;
    if (randolph_is_ready())
    {
        Result = 1;
    }

    SetRandomizerSafe(bIsSafe);

    return Result;
}

int main (void)
{
    // Make sure to set local properly, to allow for URLEncode to handle utf8.
    setlocale(LC_ALL, "");

    randolph_startup();
    RUN_TEST(TestRandom);

#if 1
    RUN_TEST(TestCreateHMAC);
    RUN_TEST(TestTruncateHMAC);

    RUN_TEST(TestIsValidKey);
    RUN_TEST(TestNormalizeKey);
    RUN_TEST(TestGenerateSecretFromSeed);
    RUN_TEST(TestGenerateSecret);
    RUN_TEST(TestGenerateSecretEntropy);
    RUN_TEST(TestGenerateKeyFromSecret);
    RUN_TEST(TestGenerateKey);

    RUN_TEST(TestUpperCase);
#endif
    RUN_TEST(TestHexify);
    RUN_TEST(TestURLEncode);

    RUN_TEST(TestToByteArray);
    RUN_TEST(TestCalculateHOTP);
    RUN_TEST(TestVerifyHOTP);
    RUN_TEST(TestCalculateTOTP);
    RUN_TEST(TestVerifyTOTP);
    RUN_TEST(TestMakeStringFromOTP);
    RUN_TEST(TestGenerateAuthURL);

    RUN_TEST(TestTiming);

    randolph_shutdown();

    return 0;
}