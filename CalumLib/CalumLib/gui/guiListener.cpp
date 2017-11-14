#include "guiListener.h"

#include "events/eventSystem.h"

GUIListener::GUIListener()
{
}

GUIListener::~GUIListener()
{
	removeEvents();
}

void GUIListener::registerEvents()
{
}

void GUIListener::removeEvents()
{
	gpEventSystem->removeListenerFromAllEvents(this);
}

void GUIListener::handleEvent(const Event& theEvent)
{
}