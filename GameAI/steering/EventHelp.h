#ifndef EVENT_HELP_H
#define EVENT_HELP_H

#include "Event.h"

class EventHelp : public Event
{
	public:
		EventHelp() :Event(EVENT_TOGGLE_HELP) {};
		~EventHelp() {};
};

#endif