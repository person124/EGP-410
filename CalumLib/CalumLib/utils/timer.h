#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

#include "utils/trackable.h"

class Timer : public Trackable
{
	public:
		Timer();
		~Timer();

		void start();
		void stop();

		double getElapsedTime() const;
		void sleepUntilElapsed(double ms);
		void pause(bool shouldPause);

		double getFactor() const { return mFactor; };
		void multFactor(double mult) { mLastFactor = mFactor; mFactor *= mult; };
		void setFactor(double theFactor) { mLastFactor = mFactor; mFactor = theFactor; };
		void restoreLastfactor() { mFactor = mLastFactor; };
	private:
		double calcDifferenceInMS(LARGE_INTEGER* from, LARGE_INTEGER* to) const;

		LARGE_INTEGER* mStartTime;
		LARGE_INTEGER* mEndTime;
		LARGE_INTEGER* mTimerFrequency;

		double mElapsedTime;
		double mFactor;
		double mLastFactor;

		bool mPaused;
};

#endif