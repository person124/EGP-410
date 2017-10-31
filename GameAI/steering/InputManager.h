#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <allegro5\allegro.h>

#include "Event.h"

#include "GameValueTypes.h"

#include "Trackable.h"

enum Keys
{
	KEYS_ESCAPE, //Close Game
	KEYS_F, //Add Unit
	KEYS_I, //Spawn 5 Units
	KEYS_D, //Delete
	KEYS_TAB, //Clear Units
	KEYS_O, //Open Debug Menu
	KEYS_MOD_UP, // +
	KEYS_MOD_DOWN, //-
	KEYS_SPACE, //Pause
	KEYS_QUESTION, //Change GUI Color
	KEYS_Z, //Reset GUI Color
	KEYS_TILDE, //Toggle Help Menu
	KEYS_COUNT
};

struct KeyInput
{
	KeyInput() {};
	KeyInput(int allegroKey, Event* mEvent)
		:mAllegroKey(allegroKey), mPressed(false), mEvent(mEvent) {};
	int mAllegroKey;
	bool mPressed;
	Event* mEvent;
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
		int mMouseX, mMouseY;

		const static int TOTAL_KEYS = KEYS_COUNT + MOD_NUM_TYPES;
		KeyInput mKeys[TOTAL_KEYS];

		bool mCTRL = false;
};

#endif