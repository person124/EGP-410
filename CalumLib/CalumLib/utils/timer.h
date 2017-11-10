#ifndef TIMER_H
#define TIMER_H

#include "utils/trackable.h"

typedef long clock_t;

class Timer : public Trackable
{
	public:
		Timer();
		~Timer();

		void start();
		void stop();

		double getElapsedTime() const;
		void sleepUntilElapsed(double ms);
	public:
		clock_t* mpStart;
		clock_t* mpEnd;
};

#endif