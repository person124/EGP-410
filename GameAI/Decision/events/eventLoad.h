#ifndef EVENT_LOAD_H
#define EVENT_LOAD_H

#include "events/event.h"

class EventLoad : public Event
{
public:
	EventLoad() :Event(EVENT_LOAD) {};
	~EventLoad() {};
};

#endif