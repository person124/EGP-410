#ifndef EVENT_KEYPRESS_H
#define EVENT_KEYPRESS_H

#include "events/event.h"

enum Keys
{
	KEYS_QUIT, //Quit Game
	KEYS_UP,
	KEYS_DOWN,
	KEYS_LEFT,
	KEYS_RIGHT,
	KEYS_CONFIRM,
	KEYS_CAMERA_UP,
	KEYS_CAMERA_DOWN,
	KEYS_CAMERA_LEFT,
	KEYS_CAMERA_RIGHT,
	KEYS_TOGGLE_SOLIDITY,
	KEYS_SAVE_MAP,
	KEYS_LOAD_MAP,
	KEYS_COUNT
};

class EventKeypress : public Event
{
	public:
		EventKeypress(Keys key) : Event(EVENT_KEYPRESS) { mKey = key; };
		~EventKeypress() {};

		Keys getKey() const { return mKey; };
	private:
		Keys mKey;
};

#endif