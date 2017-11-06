#include "event.h"

Event::Event(EventType type)
{
	mType = type;
}

Event::~Event()
{
}

const std::string& Event::getEventName() const
{
	if( mType > INVALID_EVENT_TYPE && mType < NUM_EVENT_TYPES )
		return EVENT_NAMES[mType];
	else
	{
		static const std::string nullString;
		return nullString;
	}
}