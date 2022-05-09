// Copyright (c) blurryroots innovation qanat OÜ

#pragma once

#ifndef _H_ARC4_NIX_H_
#define _H_ARC4_NIX_H_

#if !defined(_WIN32)
#pragma message ( "Going to define randolph for *nix ..." )

#include <stdlib.h>

int
randolph_startup(void)
{
	return 1;
}

int
randolph_shutdown(void)
{
	return 1;
}

int
randolph_is_ready(void)
{
	return 1;
}

int
randolph_seed(uint32_t seed)
{
#if WITH_ARC4RANDOM
	//
#else
	srand(seed);
#endif
}

void
_randolph_buffer(void* buffer, size_t buffer_size)
{
#if WITH_ARC4RANDOM
	arc4random_buf(buffer, buffer_size);
#else
	size_t block_size = buffer_size < sizeof(int) ? buffer_size : sizeof(int);
	size_t block_count = buffer_size / block_size;
	int* buffer_head = buffer;
	for (size_t block_index = 0; block_index <  block_count; ++block_index)
	{
		int block = rand();
		memcpy(buffer_head, &block, block_size);
		buffer_head += block_index * block_size;
	}

	size_t bytes_rest = buffer_size % block_size;
	if(0 < bytes_rest)
	{
		int block = rand();
		memcpy(buffer_head, &block, bytes_rest);
	}
#endif
}

int
randolph_buffer(void* buffer, size_t buffer_size)
{
	if (NULL == buffer || 0 == buffer_size) return 0;

	_randolph_buffer(buffer, buffer_size);
}

uint32_t
randolph_int(void)
{
#if WITH_ARC4RANDOM
	return arc4random();
#else
	return rand();
#endif
}

uint32_t
randolph_int_uniform(uint32_t upper_bound)
{
#if WITH_ARC4RANDOM
	return arc4random_uniform(upper_bound);
#else
	return randolph_int() % upper_bound;
#endif
}

#endif

#endif