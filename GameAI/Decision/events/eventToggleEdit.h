#ifndef EVENT_TOGGLE_EDIT_H
#define EVENT_TOGGLE_EDIT_H

#include "events/event.h"

class EventToggleEdit : public Event
{
	public:
		EventToggleEdit() :Event(EVENT_TOGGLE_EDIT) {};
		~EventToggleEdit() {};
};

#endif