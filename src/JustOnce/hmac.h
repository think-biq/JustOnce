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

#ifndef HMAC_H_
#define HMAC_H_

#include <stdint.h>
#include <string.h>
#include <sha/sha.h>

/** SHA-1 Block size */
#ifndef SHA_BLOCKSIZE
#define SHA_BLOCKSIZE 64
#endif

/**
* Generates HMAC from given data.
* @param HMAC Generated HMAC. Buffer needs to be at least SHA1_DIGEST_SIZE (20) bytes in size.
* @param Secret Secret key. 
* @param SecretLength Lenght of the key.
* @param Data Data to encode.
* @param DataLength Size of the data given.
* @returns Length of HMAC
*/
size_t CreateHMAC(
	uint8_t* HMAC,
	const uint8_t* Secret,
	const size_t SecretLength,
	const uint8_t* Data,
	const size_t DataLength
);

/**
* Truncates given HMAC to the specified number of digits and reshapes it into integral type.
* @param HMAC Target HMAC. Buffer is assumed to be SHA1_DIGEST_SIZE (20) bytes in size.
* @returns Truncated HMAC
*/
int TruncateHMAC(const uint8_t* HMAC, size_t Digits);

#endif // HMAC_H_
