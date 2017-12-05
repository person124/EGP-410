#include "timer.h"

#include <ctime>

Timer::Timer()
{
	mpStart = new clock_t;
	mpEnd = new clock_t;

	*mpStart = 0;
	*mpEnd = 0;
}

Timer::~Timer()
{
	delete mpStart;
	delete mpEnd;
}

void Timer::start()
{
	*mpStart = clock();
	*mpEnd = 0;
}

void Timer::stop()
{
	*mpEnd = clock();
}

void Timer::reset()
{
	clock_t time = clock();
	*mpStart = time;
	*mpEnd = time;
}

double Timer::getElapsedTime() const
{
	if (*mpEnd != 0)
		return ((double) (*mpEnd - *mpStart)) / CLOCKS_PER_SEC;

	clock_t current;
	current = clock();
	return ((double) (current - *mpStart)) / CLOCKS_PER_SEC;
}

void Timer::sleepUntilElapsed(double ms)
{
	clock_t current, lastTime;
	current = clock();

	double timeToSleep = ms;
	
	while (timeToSleep > 0.0)
	{
		lastTime = current;
		current = clock();

		double timeElapsed = current - lastTime;
		timeToSleep -= timeElapsed;
	}
}