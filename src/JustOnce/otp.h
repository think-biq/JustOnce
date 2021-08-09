/*
The MIT License (MIT)

Copyright (c) blurryroots innovation qanat OÜ

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdint.h>
#include <string.h>
#include <ShaOne/sha.h>

enum otp_error_t_
{
	OTP_SUCCESS,
	OTP_KEY_NULL,
	OTP_KEY_LENGTH_INVALID,
	OTP_KEY_DECODE_ERROR,
	OTP_DIGITS_INVALID,
	OTP_HMAC_ERROR
};
typedef enum otp_error_t_ otp_error_t;

const char* GetErrorName(otp_error_t State);

void ToByteArray(uint8_t* ByteArray, int64_t Data);

int CalculateHOTP(const char* Key, int64_t Counter, size_t Digits, otp_error_t* State);

int VerifyHOTP(int64_t HTOP, const char* Key, int64_t Counter, size_t Digits, otp_error_t* State);

int CalculateTOTP(const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits, otp_error_t* State);

int VerifyTOTP(int64_t TOTP, const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits,  otp_error_t* State);

char* MakeStringFromOTP(int64_t HTOP, size_t Digits);