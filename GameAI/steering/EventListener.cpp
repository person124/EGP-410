// MadeByCalum
#include "EventListener.h"

#include "EventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	if (gpEventSystem != NULL)
		gpEventSystem->removeListenerFromAllEvents(this);
}