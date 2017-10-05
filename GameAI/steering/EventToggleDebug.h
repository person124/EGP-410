#ifndef EVENT_TOGGLE_DEBUG_H
#define EVENT_TOGGLE_DEBUG_H

#include "Event.h"

class EventToggleDebug : public Event
{
	public:
		EventToggleDebug() :Event(EVENT_TOGGLE_DEBUG) {};
		~EventToggleDebug() {};
};

#endif