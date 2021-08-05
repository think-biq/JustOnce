/**
* @file re_hmac.h  Interface to HMAC functions
*
* Copyright (C) 2010 Creytiv.com
*/

#ifndef HMAC_H_
#define HMAC_H_ (1)

#include <stdint.h>

/**
* Generates HMAC from given data.
* @param Secret Secret key.
* @param SecretLength Lenght of the key.
* @param Data Data to encode.
* @param DataLength Size of the data given.
* @param HMAC Generated HMAC.
* @param HMACLength Size of the hash generated.
*/
void CreateSHA1HMAC(
	const uint8_t* Secret,
	size_t SecretLength,
	const uint8_t* Data,
	size_t DataLength,
	uint8_t* HMAC,
	size_t* HMACLength
);

#endif // HMAC_H_
