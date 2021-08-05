int64_t GetUnixTimeNow();

int64_t GetTimeFrame(int64_t UnixTime, size_t Interval);

int64_t GetTimeFrameNow(size_t Interval);

int CalculateHOTP(const char* Key, int64_t Data, size_t Digits);

char* MakeStringFromHOTP(int64_t Hash, size_t Digits);