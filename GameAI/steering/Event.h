#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <Trackable.h>

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	EVENT_QUIT,
	EVENT_MOUSE_CLICK,
	EVENT_ADD_AI,
	EVENT_DELETE_AI,
	EVENT_CLEAR_AI,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] =
{
"Quit Game Event",
"Mouse Click Event",
"Add AI Arrive/Seek Event",
"Remove AI Event",
"Clear All AI Event"
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