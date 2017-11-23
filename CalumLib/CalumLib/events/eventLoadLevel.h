#ifndef EVENT_LOAD_LEVEL_H
#define EVENT_LOAD_LEVEL_H

#include "events/event.h"

class EventLoadLevel : public Event
{
	public:
		EventLoadLevel(const char* levelName) : Event(EVENT_LOAD_LEVEL) { mLevelName = levelName; }
		~EventLoadLevel() {};

		const char* getLevelName() { return mLevelName; };
	private:
		const char* mLevelName;
};

#endif