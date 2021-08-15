

// time.h

int TestTiming()
{
    int Passed = 1;

    {
        int64_t ExpectedTime = (int64_t)time(NULL);
        int64_t UnixTime = GetUnixTimeNow();
        Passed &= Check("GetUnixTimeNow", sizeof(int), &ExpectedTime, &UnixTime,
            "Expected %i, got %i.", ExpectedTime, UnixTime
        );

        int64_t ExpectedTimeFrame = ExpectedTime / 30;
        int64_t TimeFrame = GetTimeFrameNow(30);
        Passed &= Check("GetTimeFrameNow", sizeof(int), &ExpectedTimeFrame, &TimeFrame,
            "Expected %i, got %i.", ExpectedTimeFrame, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(30, 30);
        Passed &= Check("GetTimeFrame@30:30", sizeof(int), &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(59, 30);
        Passed &= Check("GetTimeFrame@59:30", sizeof(int), &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 2;
        int64_t TimeFrame = GetTimeFrame(60, 30);
        Passed &= Check("GetTimeFrame@60:30", sizeof(int), &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    return Passed;
}