#ifndef EVENT_PAUSE_H
#define EVENT_PAUSE_H

#include "Event.h"

class EventPause : public Event
{
	public:
		EventPause() :Event(EVENT_PAUSE) {};
		~EventPause() {};
};

#endif