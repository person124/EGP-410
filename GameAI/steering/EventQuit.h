#ifndef EVENT_QUIT_H
#define EVENT_QUIT_H

#include "Event.h"

class EventQuit : public Event
{
	public:
		EventQuit() :Event(EVENT_QUIT) {};
		~EventQuit() {};
};

#endif