#ifndef KEY_H_
#define KEY_H_

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