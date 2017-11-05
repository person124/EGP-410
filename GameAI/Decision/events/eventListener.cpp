#include "eventListener.h"

#include "eventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	if( gpEventSystem != NULL )
		gpEventSystem->removeListenerFromAllEvents(this);
}
