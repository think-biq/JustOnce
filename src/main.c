#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <baseencode/baseencode.h>
#include <JustOnce/JustOnce.h>

int main (void) {
    const char* Secret = "CAFECAFECAFECAFECAFE";

    int Digits = 6;
    int Interval = 30;

    int HMAC;
    {
        baseencode_error_t ErrorCode;
        char* Key = base32_encode((unsigned char*)Secret, strlen(Secret), &ErrorCode);
        if (SUCCESS != ErrorCode)
        {
            printf("Could not encode secret! (ErrorCode: %i)\n", ErrorCode);
            exit(0);
        }

        int64_t TimeFrame = GetTimeFrameNow(Interval);
        HMAC = CalculateHOTP(Key, TimeFrame, Digits);

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