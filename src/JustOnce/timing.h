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
/*! \file timing.h
    \brief timing
    
    ^^
*/

#include <stddef.h>
#include <stdint.h>

#ifndef TIMING_H
#define TIMING_H

/**
* GetUnixTimeNow
*
* @returns Unix time stamp of the time of calling.
*/
int64_t GetUnixTimeNow();

/**
* GetTimeFrame
* 
* @param UnixTime
* @param Interval
* @returns Timeframe for given unix time.
*/
int64_t GetTimeFrame(int64_t UnixTime, size_t Interval);

/**
* GetTimeFrameProgress
* 
* @param UnixTime
* @param Interval
* @returns Timeframe for given unix time.
*/
int64_t GetTimeFrameProgress(int64_t UnixTime, size_t Interval);

/**
* GetTimeFrameNow
* 
* @param Interval
* @returns Timeframe for the time of calling.
*/
int64_t GetTimeFrameNow(size_t Interval);

#endif