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
/*! \file key.h
    \brief key
    
    ^^
*/

#ifndef KEY_H_
#define KEY_H_

/**
* Toggle the algortihm used for randomization. Uses cryptographically safe arc4random implementation if activated. 
* 
* @param bUseSafe Wether to active cryptocraphically safe random or deterministic random.
*/
void SetRandomizerSafe(int bUseSafe);

/**
* Configures seed value to be used by randomizer.
* 
* @param Seed Configures seed value.
*/
void SetRandomizerSeed(int Seed);

/**
* Checks if given key is valid.
* 
* @param Key Key to check.
* @returns 1 if valid. 0 otherwise.
*/
int IsValidKey(const char* Key);

/**
* Normalizes given key in place.
* 
* If key < 32, it will append = for each missing character. If key > 32 it will
* cutoff key at length 32. Also makes sure key is uppercase.
* 
* @param Key Key to normalize.
*/
void NormalizeKey(char** Key);

/**
* Creates new secret from given seed.
* 
* @param Seed
* @returns Secret.
*/
char* GenerateSecretFromSeed(const char* Seed);

/**
* Creates new secret from random seed.
*
* @returns Random Secret.
*/
char* GenerateSecret();

/**
* Creates new key from given secret.
* 
* @param Secret
* @returns Key
*/
char* GenerateKeyFromSecret(const char* Secret);

/**
* Creates new key from seed.
* 
* @param Seed
* @returns Key
*/
char* GenerateKeyFromSeed(const char* Seed);

/**
* Creates new key from random seed.
* 
* @returns Key
*/
char* GenerateKey();

#endif