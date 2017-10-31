#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <Trackable.h>

enum EventType
{
	EVENT_INVALID = -1,
	EVENT_QUIT,
	EVENT_MOUSE_MOVE,
	EVENT_MOUSE_CLICK,
	EVENT_ADD_AI,
	EVENT_DELETE_AI,
	EVENT_CLEAR_AI,
	EVENT_TOGGLE_DEBUG,
	EVENT_MODIFY,
	EVENT_MODIFY_STAT,
	EVENT_PAUSE,
	EVENT_CHANGE_COLOR,
	EVENT_SET_COLOR,
	EVENT_SAVE,
	EVENT_LOAD,
	EVENT_TOGGLE_HELP,
	EVENT_NUM_TYPES
};

const std::string EVENT_NAMES[EVENT_NUM_TYPES] =
{
"Quit Game Event",
"Mose Move Event",
"Mouse Click Event",
"Add AI Seek/Flee Event",
"Delete AI Event",
"Clear All AI Event",
"Toggle Debug Option Event",
"+/- Debug Stat Event",
"Switch Debug Stat Event",
"Pause Game Event",
"Change GUI Color Event",
"Set GUI Color Event",
"Save GameValues",
"Load GameValues",
"Toggle Help Display"
};

class Event : public Trackable
{
	public:
		Event() { mType = EVENT_INVALID; };
		Event(EventType type);
		virtual ~Event();

		EventType getType() const { return mType; };
		const std::string& getEventName() const;
	private:
		EventType mType;
};

#endif