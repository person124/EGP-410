#ifndef EVENT_CLICK_H
#define EVENT_CLICK_H

#include "events/event.h"

enum MouseButton
{
	left_mouse_button,
	right_mouse_button
};

class EventClick : public Event
{
	public:
		EventClick(int x, int y, MouseButton b) :Event(EVENT_CLICK)
		{
			mX = x;
			mY = y;
			mButton = b;
		}
		~EventClick() {};

		int getX() const { return mX; };
		int getY() const { return mY; };
		MouseButton getButton() const { return mButton; };
	private:
		int mX, mY;
		MouseButton mButton;
};

#endif