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

#ifndef KEY_H_
#define KEY_H_

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
void SetRandomizerSafe(int bUseSafe);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
void SetRandomizerSeed(int Seed);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
void NormalizeKey(char** Key);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
char* GenerateSecretFromSeed(const char* Seed);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
char* GenerateSecret();

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
char* GenerateKeyFromSecret(const char* Secret);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
char* GenerateKeyFromSeed(const char* Seed);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
char* GenerateKey();

#endif