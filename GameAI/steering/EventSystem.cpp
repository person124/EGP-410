// MadeByCalum
#include "EventSystem.h"

#include "Event.h"
#include "EventListener.h"

using namespace std;

EventSystem* gpEventSystem = NULL;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

void EventSystem::fireEvent(const Event& theEvent)
{
	dispatchAllEvents(theEvent);
}

void EventSystem::addListener(EventType type, EventListener* listener)
{
	mListenerMap.insert(pair<EventType, EventListener*>(type, listener));
}

void EventSystem::removeListener(EventType type, EventListener* listener)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;

	ret = mListenerMap.equal_range(type);
	multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
		if (iter->second == listener)
		{
			mListenerMap.erase(iter);
			break;
		}
}

void EventSystem::removeListenerFromAllEvents(EventListener* listener)
{
	multimap<EventType, EventListener*>::iterator iter;
	bool allTheWay = false;

	while (!allTheWay)
	{
		allTheWay = true;
		for (iter = mListenerMap.begin(); iter != mListenerMap.end(); ++iter)
			if (iter->second == listener)
			{
				mListenerMap.erase(iter);
				allTheWay = false;
				break;
			}
	}
}

void EventSystem::dispatchAllEvents(const Event& theEvent)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range(theEvent.getType());

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
		iter->second->handleEvent(theEvent);
}