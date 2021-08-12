#include "misc.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char* MakeUpperCase(const char* String)
{
    if (NULL == String)
    {
        return NULL;
    }

    const size_t Length = strlen(String);
    char* Copy = strdup(String);
    ToUpperCase(&Copy);

    return Copy;
}

void ToUpperCase(char** String)
{
    if (NULL == String || NULL == *String)
    {
        return;
    }

    // Make sure key is upper case.
    char* StringPtr = *String;
    for (size_t Index = 0; Index < strlen(StringPtr); ++Index)
    {
        if (StringPtr[Index] >= 'a' && StringPtr[Index] <= 'z')
        {
            StringPtr[Index] = StringPtr[Index] - 32;
        }
    }	
}

char* Hexify(const uint8_t* Buffer, size_t Count)
{
    if (NULL == Buffer)
    {
        return NULL;
    }

    char* Hash = calloc(1, Count*2+1);
    for (size_t Index = 0; Index < Count; ++Index)
    {
        char Hex[3];
        snprintf(Hex, 3, "%02x", Buffer[Index]);
        strcat(Hash, Hex);
    }

    Hash[Count*2] = '\0';
    return Hash;
}

char from_hex(char ch)
{
  /* Adapted from Public Domain implementation by https://www.geekhideout.com/urlcode.shtml*/
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

char to_hex(char code) 
{
  /* Adapted from Public Domain implementation by https://www.geekhideout.com/urlcode.shtml*/
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

char* URLEncode(const char* Raw)
{
  /* Adapted from Public Domain implementation by https://www.geekhideout.com/urlcode.shtml*/
  char* RawCpy = strdup(Raw);
  char *pstr = RawCpy, *buf = malloc(strlen(RawCpy) * 3 + 1), *pbuf = buf;
  while (*pstr)
  {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') 
      *pbuf++ = *pstr;
    else if (*pstr == ' ') 
    {
      *pbuf++ = '%'; *pbuf++ = '2'; *pbuf++ = '0';
    }
    else 
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  free(RawCpy);

  return buf;
}

char* URLDecode(const char* Encoded)
{
  /* Adapted from Public Domain implementation by https://www.geekhideout.com/urlcode.shtml*/
  char* EncodedCpy = strdup(Encoded);
  char *pstr = EncodedCpy, *buf = malloc(strlen(EncodedCpy) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') { 
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  free(EncodedCpy);

  return buf;  
}