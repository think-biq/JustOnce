
#ifndef TESTLY_ASSERT_H_
#define TESTLY_ASSERT_H_

#ifndef TESTLY_ASSERT_DISABLED
void Assert(int DataSize, const char* Name, const void* Expected, const void* Actual, const char* FailFMT, ...);
#else
#define Assert(...) {}
#endif

#endif