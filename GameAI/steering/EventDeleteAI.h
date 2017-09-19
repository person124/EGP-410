#ifndef EVENT_DELETE_AI_H
#define EVENT_DELETE_AI_H

#include "Event.h"

class EventDeleteAI : public Event
{
	public:
		EventDeleteAI() :Event(EVENT_DELETE_AI) {};
		~EventDeleteAI() {};
};

#endif