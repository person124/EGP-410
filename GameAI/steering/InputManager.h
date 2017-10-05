#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <allegro5\allegro.h>

#include "Event.h"

enum Keys
{
	KEYS_ESCAPE,
	KEYS_S, //Seek
	KEYS_F, //Flee
	KEYS_D, //Delete
	KEYS_C, //Clear
	KEYS_I, //Display Debug Info
	KEYS_MOD_UP, // +
	KEYS_MOD_DOWN, //-
	KEYS_V, //Mod Velocity
	KEYS_R, //Mod Radius
	KEYS_A, //Mod Angular Speed
	KEYS_COUNT
};

struct KeyInput
{
	KeyInput() {};
	KeyInput(int allegroKey, Event& mEvent)
		:mAllegroKey(allegroKey), mPressed(false), mEvent(mEvent) {};
	int mAllegroKey;
	bool mPressed;
	Event mEvent;
};

class InputManager
{
	public:
		InputManager();
		~InputManager();
		bool init();
		void update();
	private:
		ALLEGRO_KEYBOARD_STATE mKeyState;

		ALLEGRO_MOUSE_STATE mMouseState;
		int mMouseX, mMouseY;

		KeyInput mKeys[KEYS_COUNT];
};

#endif