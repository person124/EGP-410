#ifndef EVENT_CHANGE_COLOR_H
#define EVENT_CHANGE_COLOR_H

#include "Event.h"

class EventChangeColor : public Event
{
	public:
		EventChangeColor() :Event(EVENT_CHANGE_COLOR) {};
		~EventChangeColor() {};
};

#endif