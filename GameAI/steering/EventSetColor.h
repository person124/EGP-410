#ifndef EVENT_SET_COLOR_H
#define EVENT_SET_COLOR_H

#include "Event.h"

class EventSetColor : public Event
{
	public:
		EventSetColor() :Event(EVENT_SET_COLOR) {};
		~EventSetColor() {};
};

#endif