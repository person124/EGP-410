#ifndef EVENT_SAVE_H
#define EVENT_SAVE_H

#include "events/event.h"

class EventSave : public Event
{
	public:
		EventSave() :Event(EVENT_SAVE) {};
		~EventSave() {};
};

#endif