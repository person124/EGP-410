#ifndef EVENT_H
#define EVENT_H

#include "utils/trackable.h"

#include <string>

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	EVENT_QUIT,
	EVENT_CLICK,
	EVENT_KEYPRESS,
	EVENT_SWITCH_STATE,
	EVENT_LOAD_LEVEL,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = {
	"Quit Event",
	"Mouse Click Event",
	"Keypress Event",
	"Switch Game State Event",
	"Load Level Event"
};

class Event : public Trackable
{
	public:
		Event() { mType = INVALID_EVENT_TYPE; };
		Event(EventType type);
		virtual ~Event();

		EventType getType() const { return mType; };
		const std::string& getEventName() const;
	private:
		EventType mType;
};

#endif