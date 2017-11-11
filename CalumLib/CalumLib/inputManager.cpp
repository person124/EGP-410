#include "inputManager.h"

#include "ioUtils.h"

#include "events/eventSystem.h"
#include "events/eventQuit.h"
#include "events/eventClick.h"
#include "events/eventDijkstra.h"
#include "events/eventAStar.h"
#include "events/eventToggleEdit.h"
#include "events/eventSave.h"
#include "events/eventLoad.h"

InputManager::InputManager()
{
	mKeys[KEYS_QUIT] = KeyInput(ALLEGRO_KEY_ESCAPE, new EventQuit());

	mKeys[KEYS_DIJKSTRA] = KeyInput(ALLEGRO_KEY_D, new EventDijkstra());
	mKeys[KEYS_A_STAR] = KeyInput(ALLEGRO_KEY_A, new EventAStar());

	mKeys[KEYS_TOGGLE_EDIT] = KeyInput(ALLEGRO_KEY_E, new EventToggleEdit());

	mKeys[KEYS_SAVE] = KeyInput(ALLEGRO_KEY_Q, new EventSave());
	mKeys[KEYS_LOAD] = KeyInput(ALLEGRO_KEY_P, new EventLoad());
}

InputManager::~InputManager()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();

	for (int i = 0; i < KEYS_COUNT; i++)
		delete mKeys[i].theEvent;
}

bool InputManager::init()
{
	if (!al_install_mouse())
	{
		IOUtils::errorInitReport("mouse");
		return false;
	}

	if (!al_install_keyboard())
	{
		IOUtils::errorInitReport("keyboard");
		return false;
	}

	return true;
}

void InputManager::update()
{
	al_get_keyboard_state(&mKeyState);
	al_get_mouse_state(&mMouseState);

	//When either mouse button is pressed
	if (mMouseState.buttons & (1 | 2))
	{
		MouseButton state = (mMouseState.buttons & 1) ? left_mouse_button : right_mouse_button;
		gpEventSystem->fireEvent(EventClick(mMouseState.x, mMouseState.y, state));
	}

	//Main Loop for Checking Keys
	for (int i = 0; i < KEYS_COUNT; i++)
	{
		if (al_key_down(&mKeyState, mKeys[i].allegroKey))
		{
			if (mKeys[i].repeating || !mKeys[i].pressed)
				gpEventSystem->fireEvent(*mKeys[i].theEvent);
			mKeys[i].pressed = true;
		}
		else
			mKeys[i].pressed = false;
	}
}