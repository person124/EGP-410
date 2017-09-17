#ifndef EVENT_MOUSE_CLICK_H
#define EVENT_MOUSE_CLICK_H

#include "Event.h"

class EventMouseClick : public Event
{
	public:
		EventMouseClick(int x, int y) :Event(EVENT_MOUSE_CLICK) { mX = x; mY = y; };
		~EventMouseClick() {};

		int getX() const { return mX; };
		int getY() const { return mY; };
	private:
		int mX, mY;
};

#endif