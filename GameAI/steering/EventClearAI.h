#ifndef EVENT_CLEAR_AI_H
#define EVENT_CLEAR_AI_H

#include "Event.h"

class EventClearAI : public Event
{
	public:
		EventClearAI() :Event(EVENT_CLEAR_AI) {};
		~EventClearAI() {};
};

#endif