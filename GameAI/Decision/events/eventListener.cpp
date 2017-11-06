#include "eventListener.h"

#include "events/eventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	if( gpEventSystem != NULL )
		gpEventSystem->removeListenerFromAllEvents(this);
}
