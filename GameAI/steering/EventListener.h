// MadeByCalum
#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <Trackable.h>

class Event;

class EventListener : public Trackable
{
	public:
		EventListener();
		virtual ~EventListener();

		virtual void handleEvent(const Event& theEvent) = 0;
};

#endif