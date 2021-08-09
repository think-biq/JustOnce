

// time.h

void TestTiming()
{
    {
        int64_t ExpectedTime = (int64_t)time(NULL);
        int64_t UnixTime = GetUnixTimeNow();
        Assert(sizeof(int), "GetUnixTimeNow", TESTLY_EXIT_ON_FAIL, &ExpectedTime, &UnixTime,
            "Expected %i, got %i.", ExpectedTime, UnixTime
        );

        int64_t ExpectedTimeFrame = ExpectedTime / 30;
        int64_t TimeFrame = GetTimeFrameNow(30);
         Assert(sizeof(int), "GetTimeFrameNow", TESTLY_EXIT_ON_FAIL, &ExpectedTimeFrame, &TimeFrame,
            "Expected %i, got %i.", ExpectedTimeFrame, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(30, 30);
        Assert(sizeof(int), "GetTimeFrame@30:30", TESTLY_EXIT_ON_FAIL, &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 1;
        int64_t TimeFrame = GetTimeFrame(59, 30);
        Assert(sizeof(int), "GetTimeFrame@59:30", TESTLY_EXIT_ON_FAIL, &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }

    {
        int64_t Expected = 2;
        int64_t TimeFrame = GetTimeFrame(60, 30);
        Assert(sizeof(int), "GetTimeFrame@60:30", TESTLY_EXIT_ON_FAIL, &Expected, &TimeFrame,
            "Expected %i, got %i.", Expected, TimeFrame
        );
    }
}