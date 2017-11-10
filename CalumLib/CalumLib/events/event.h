#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "utils/trackable.h"

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	EVENT_QUIT,
	EVENT_CLICK,
	EVENT_DIJKSTRA,
	EVENT_A_STAR,
	EVENT_TOGGLE_EDIT,
	EVENT_SAVE,
	EVENT_LOAD,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = {
	"Quit Event",
	"Mouse Click Event",
	"Start Dijkstra Event",
	"Start A* Event",
	"Toggle Edit Mode Event",
	"Save Grid Event",
	"Load Grid Event"
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