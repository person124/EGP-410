#ifndef EVENT_A_STAR_H
#define EVENT_A_STAR_H

#include "events/event.h"

class EventAStar : public Event
{
	public:
		EventAStar() :Event(EVENT_A_STAR) {};
		~EventAStar() {};
};

#endif