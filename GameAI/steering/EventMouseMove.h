#ifndef EVENT_MOUSE_MOVE_H
#define EVENT_MOUSE_MOVE_H

#include "Event.h"

class EventMouseMove : public Event
{
	public:
		EventMouseMove(int x, int y) :Event(EVENT_MOUSE_MOVE)
		{
			mX = x;
			mY = y;
		};
		~EventMouseMove() {};

		int getX() const { return mX; };
		int getY() const { return mY; };
	private:
		int mX, mY;
};

#endif