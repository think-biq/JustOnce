
#undef TESTLY_ASSERT_DISABLED
#include "testly/assert.h"
#include "testly/run.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include <JustOnce/otp.h>
#include <JustOnce/timing.h>
#include <JustOnce/key.h>
#include <JustOnce/misc.h>

#define VERBOSE 0

#include "test-hmac.h"
#include "test-key.h"
#include "test-misc.h"
#include "test-otp.h"
#include "test-timing.h"

int main (void)
{
    RUN_TEST(TestCreateHMAC);
    RUN_TEST(TestTruncateHMAC);

    RUN_TEST(TestNormalizeKey);
    RUN_TEST(TestGenerateSecretFromSeed);
    RUN_TEST(TestGenerateSecret);
    //RUN_TEST(TestGenerateSecretEntropy);
    RUN_TEST(TestGenerateKeyFromSecret);
    RUN_TEST(TestGenerateKey);

    RUN_TEST(TestUpperCase);
    RUN_TEST(TestHexify);

    RUN_TEST(TestToByteArray);
    RUN_TEST(TestCalculateHOTP);
    RUN_TEST(TestVerifyHOTP);
    RUN_TEST(TestCalculateTOTP);
    RUN_TEST(TestVerifyTOTP);
    RUN_TEST(TestMakeStringFromOTP);

    RUN_TEST(TestTiming);    

    return 0;
}