#include "Event.h"

Event::Event(EventType type)
{
	mType = type;
}

Event::~Event()
{
}

const std::string& Event::getEventName() const
{
	if (mType > EVENT_INVALID && mType < EVENT_NUM_TYPES)
		return EVENT_NAMES[mType];
	else
	{
		static const std::string nullString;
		return nullString;
	}
}