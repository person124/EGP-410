#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "events/eventKeypress.h"

#include "utils/trackable.h"

#include <allegro5/allegro.h>

class Event;

struct KeyInput : public Trackable
{
	KeyInput() {};
	KeyInput(int allegroKeyCode, Event* e, bool repeat = false)
	{
		allegroKey = allegroKeyCode;
		theEvent = e;
		repeating = repeat;

		pressed = false;
	}
	~KeyInput() {};

	int allegroKey;
	Event* theEvent;
	bool pressed;
	bool repeating;
};

class InputManager : public Trackable
{
	public:
		InputManager();
		~InputManager();

		bool init();
		void update();
	private:
		ALLEGRO_KEYBOARD_STATE mKeyState;

		ALLEGRO_MOUSE_STATE mMouseState;

		KeyInput mKeys[KEYS_COUNT];
};

#endif