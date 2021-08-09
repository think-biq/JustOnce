
#ifndef TESTLY_ASSERT_H_
#define TESTLY_ASSERT_H_

#define TESTLY_EXIT_ON_FAIL 0

#ifndef TESTLY_ASSERT_DISABLED
void Fail(const char* Name, int bExitOnFail, const char* FailFMT, ...);
void Assert(int DataSize, const char* Name, int bExitOnFail, const void* Expected, const void* Actual, const char* FailFMT, ...);
#else
#define Fail(...) {}
#define Assert(...) {}
#endif

#endif