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
/*! \file otp.h
    \brief otp
    
    ^^
*/

#include <stdint.h>
#include <string.h>
#include <ShaOne/sha.h>

/** Defining OTP error codes. */
enum otp_error_t_
{
	OTP_SUCCESS, /**< Operation successful. */
	OTP_KEY_NULL, /**< Given key was NULL. */
	OTP_KEY_LENGTH_INVALID, /**< Key length invalid (!= 32) */
	OTP_KEY_DECODE_ERROR, /**< Could not decode key from base32 string. */
	OTP_DIGITS_INVALID, /**< Target number of digits invalid. */
	OTP_HMAC_ERROR /**< Critical error creating HMAC. */
};

/** OTP error codes. */
typedef enum otp_error_t_ otp_error_t;

/**
* Look up error code string.
* 
* @param State Error state.
* @returns String version of state.
*/
const char* GetErrorName(otp_error_t State);

/**
* Transfroms given data to byte-wise array.
* 
* @param Data Data to expand.
* @param ByteArray ByteArray representing given data.
*/
void ToByteArray(uint8_t* ByteArray, int64_t Data);

/**
* CalculateHOTP
* 
* @param Key
* @param Counter
* @param Digits
* @param Key
* @returns HOTP
*/
int CalculateHOTP(const char* Key, int64_t Counter, size_t Digits, otp_error_t* State);

/**
* VerifyHOTP
* 
* @param HTOP
* @param Key
* @param Counter
* @param Digits
* @param State
* @returns True of false.
*/
int VerifyHOTP(int64_t HTOP, const char* Key, int64_t Counter, size_t Digits, otp_error_t* State);

/**
* CalculateTOTP
* 
* @param Key
* @param Timestamp
* @param Interval
* @param Digits
* @param State
* @returns TOTP
*/
int CalculateTOTP(const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits, otp_error_t* State);

/**
* VerifyTOTP
* 
* @param HTOP
* @param Key
* @param Counter
* @param Digits
* @param State
* @returns TOTP
*/
int VerifyTOTP(int64_t TOTP, const char* Key, int64_t Timestamp, int64_t Interval, size_t Digits,  otp_error_t* State);

/**
* MakeStringFromOTP
* 
* @param Key
* @param Counter
* @param Digits
* @param Key
* @returns HOTP
*/
char* MakeStringFromOTP(int64_t HTOP, size_t Digits);