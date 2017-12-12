#ifndef EVENT_GAME_OVER_H
#define EVENT_GAME_OVER_H

#include "events/event.h"

class EventGameOver : public Event
{
	public:
		EventGameOver(int score) : Event(EVENT_GAME_OVER)
		{
			mScore = score;
		};
		~EventGameOver() {};

		int getScore() const { return mScore; };
	private:
		int mScore;
};

#endif