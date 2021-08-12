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
/*! \file misc.h
    \brief misc
    
    ^^
*/

#ifndef MISC_H_
#define MISC_H_

#include <stdint.h>
#include <string.h>

/**
* Creates an uppercase copy of the given string. Should be freed after usage.
* 
* @param String String to change.
* @returns Uppercase string.
*/
char* MakeUpperCase(const char* String);

/**
* Changes given string to uppercase version in place.
* 
* @param String Pointer to string which should be uppercased.
*/
void ToUpperCase(char** String);

/**
* Creates a hexadecimal version of the given buffer. Should be freed after usage.
* 
* @param Buffer Data buffer.
* @param Count Element size of buffer.
* @returns Newly allocate hex string.
*/
char* Hexify(const uint8_t* Buffer, size_t Count);

/**
* Creates URL safe encoding from raw string.
* 
* @param Raw String to be encoded.
* @returns URL encoded string.
*/
char* URLEncode(const char* Raw);

/**
* Creates raw string from URL safe encoding.
* 
* @param Encoded Encoded string.
* @returns Raw string.
*/
char* URLDecode(const char* Encoded);

#endif