# JustOnce

A framework for one-time password (OTP) generation.

## Setup

Clone the repository recursively:

```bash
git clone --recursive https://github.com/think-biq/JustOnce .
```

To build the library:

```bash
make
```

Will generate the build environment to ./staging through cmake, and builds the
library.

To run the tests:

```bash
make run-test
```

Will build a test executable using the [testly](https://github.com/think-biq/testly) test library.

To generate doxygen documentation:

```bash
make docs
```

Will build doxygen html output and put it into docs/html.

## Examples

### Create TOTP

```c
#include <JustOnce/otp.h>
#include <stdio.h>

int main(void)
{
	int Digits = 6;
	int64_t Timestamp = 433512000;
	int64_t Interval = 30;	
	otp_error_t State;

	// Generates random OTP key (32 character long base32 encoded string).
	char* Key = GenerateKey();
	printf("Generating TOTP using Key '%s' ...\n", Key);
	// Generates time-based one-time password.
	int TOTP = CalculateTOTP(Key, Timestamp, Interval, Digits, &State);
	free(Key);

	// Converts otp code to string and prepends zeros if necessary (depending on digit count).
	char* Code = MakeStringFromOTP(TOTP, Digits);
	printf("TOTP: %s (State: %s)\n", Code, GetErrorName(State));
	free(Code);

}
```

### Other examples

Feel free to stroll through the tests, to see further usage examples.

## Modules

For detailed documentation, consider building doxygen html documentation.

### HMAC

Offers a SHA1 based HMAC generation.

### Key

Functionallity to generate and validate keys to be used for OTP generation.

### Misc

String case functions and url encoding.

### OTP

Generation and validation of one-time passwords.

### Timing

Time utility functions to fetch unix timestamp and generate TOTP periods.