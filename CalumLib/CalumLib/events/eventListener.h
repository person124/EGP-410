#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "utils/trackable.h"

class Event;

class EventListener : public Trackable
{
	public:
		EventListener();
		virtual ~EventListener();

		virtual void handleEvent(const Event& theEvent) = 0;
};

#endif