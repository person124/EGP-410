#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <Trackable.h>

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	EVENT_QUIT,
	EVENT_MOUSE_CLICK,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] =
{
"Quit Game Event",
"Mouse Click Event"
};

class Event : public Trackable
{
	public:
		Event(EventType type);
		virtual ~Event();

		EventType getType() const { return mType; };
		const std::string& getEventName() const;
	private:
		EventType mType;
};

#endif