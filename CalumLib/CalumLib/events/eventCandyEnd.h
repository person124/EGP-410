#ifndef EVENT_CANDY_END_H
#define EVENT_CANDY_END_H

#include "events/event.h"

class EventCandyEnd : public Event
{
	public:
		EventCandyEnd() : Event(EVENT_CANDY_END) {};
		~EventCandyEnd() {};
};

#endif