/**
* Public api for Steve Reid's public domain SHA-1 implementation.
* This file is in the public domain / CC0 (if applicable).
*
* Copyright (C) 2010 Creytiv.com
*/

#ifndef SHA_H_
#define SHA_H_ (1)

/** SHA-1 Context */
typedef struct {
    uint32_t state[5];
    /**< Context state */
    uint32_t count[2];
    /**< Counter       */
    uint8_t buffer[64]; /**< SHA-1 buffer  */
} SHA1_CTX;

/** SHA-1 Context (OpenSSL compat) */
typedef SHA1_CTX SHA_CTX;

/** SHA-1 Digest size in bytes */
#define SHA1_DIGEST_SIZE 20
/** SHA-1 Digest size in bytes (OpenSSL compat) */
#define SHA_DIGEST_LENGTH SHA1_DIGEST_SIZE

/**
* Initialize new context
*
* @param context SHA1-Context
*/
void SHA1_Init(SHA1_CTX *context);

/**
* Run your data through this
*
* @param context SHA1-Context
* @param p       Buffer to run SHA1 on
* @param len     Number of bytes
*/
void SHA1_Update(SHA1_CTX *context, const void *p, size_t len);

/**
* Add padding and return the message digest
*
* @param digest  Generated message digest
* @param context SHA1-Context
*/
void SHA1_Final(uint8_t digest[SHA1_DIGEST_SIZE], SHA1_CTX *context);

#endif // SHA_H_
