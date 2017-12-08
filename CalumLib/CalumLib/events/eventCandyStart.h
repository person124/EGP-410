#ifndef EVENT_CANDY_START_H
#define EVENT_CANDY_START_H

#include "events/event.h"

class EventCandyStart : public Event
{
	public:
		EventCandyStart() : Event(EVENT_CANDY_START) {};
		~EventCandyStart() {};
};

#endif