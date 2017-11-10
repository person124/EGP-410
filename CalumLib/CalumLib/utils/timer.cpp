#include "timer.h"

Timer::Timer()
{
	mElapsedTime = 0.0;
	mPaused = true;
	mFactor = 1.0f;
	mLastFactor = 1.0f;

	mTimerFrequency = new LARGE_INTEGER;
	QueryPerformanceFrequency(mTimerFrequency);

	mStartTime = new LARGE_INTEGER;
	mStartTime->QuadPart = 0;

	mEndTime = new LARGE_INTEGER;
	mEndTime->QuadPart = 0;
}

Timer::~Timer()
{
	delete mTimerFrequency;
	delete mStartTime;
	delete mEndTime;
}

void Timer::start()
{
	QueryPerformanceCounter(mStartTime);

	mEndTime->QuadPart = 0;

	mElapsedTime = 0.0;

	pause(false);
}

void Timer::stop()
{
	QueryPerformanceCounter(mEndTime);
	mElapsedTime = calcDifferenceInMS(mStartTime, mEndTime);
}

void Timer::pause(bool shouldPause)
{
	if (shouldPause && !mPaused)
	{
		mPaused = true;
		QueryPerformanceCounter(mEndTime);
		mElapsedTime += calcDifferenceInMS(mStartTime, mEndTime);
	}
	else if (!shouldPause && mPaused)
	{
		mPaused = false;
		QueryPerformanceCounter(mStartTime);
	}
}

double Timer::getElapsedTime() const
{
	if (mEndTime->QuadPart != 0)
		return mElapsedTime;
	else
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return calcDifferenceInMS(mStartTime, &currentTime);
	}
}

void Timer::sleepUntilElapsed(double ms)
{
	LARGE_INTEGER currentTime, lastTime;
	QueryPerformanceCounter(&currentTime);

	double timeToSleep = ms - calcDifferenceInMS(&lastTime, &currentTime);
	
	while (timeToSleep > 0.0)
	{
		lastTime = currentTime;
		QueryPerformanceCounter(&currentTime);
		double timeElapsed = calcDifferenceInMS(&lastTime, &currentTime);
		timeToSleep -= timeElapsed;

		if (timeToSleep > 10.0)
			Sleep(10);
	}
}

double Timer::calcDifferenceInMS(LARGE_INTEGER* from, LARGE_INTEGER* to) const
{
	double difference = (double) (to->QuadPart - from->QuadPart) / (double) mTimerFrequency->QuadPart;
	difference *= mFactor;
	return difference * 1000;
}