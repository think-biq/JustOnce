// Copyright (c) blurryroots innovation qanat OÜ
// .
// Abstraction for platform specific cryptographic RNGs

#pragma once

#ifndef _H_RANDOLPH_H_
#define _H_RANDOLPH_H_

#include <stdint.h>

int
randolph_startup(void);

int
randolph_shutdown(void);

int
randolph_is_ready(void);

int
randolph_seed(uint32_t seed);

int
randolph_buffer(void* buffer, size_t buffer_size);

uint32_t
randolph_int(void);

uint32_t
randolph_int_uniform(uint32_t upper_bound);

#if defined(RANDOLPH_DEFINE_ARC4)
uint32_t
arc4random(void);

void
arc4random_buf(void *buf, size_t nbytes);

uint32_t
arc4random_uniform(uint32_t upper_bound);
#endif

#endif