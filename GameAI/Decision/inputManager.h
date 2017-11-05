#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "events\event.h"

#include <allegro5\allegro.h>

#include <Trackable.h>

enum Keys
{
	KEYS_QUIT, //Quit Game
	KEYS_COUNT
};

struct KeyInput : public Trackable
{
	KeyInput() {};
	KeyInput(int allegroKey, Event* theEvent)
	{
		mAllegroKey = allegroKey;
		mEvent = theEvent;

		mPressed = false;
	}
	~KeyInput() {};

	int mAllegroKey;
	Event* mEvent;
	bool mPressed;
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