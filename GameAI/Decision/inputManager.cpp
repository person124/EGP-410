#include "inputManager.h"

#include "events\eventSystem.h"
#include "events\eventQuit.h"

InputManager::InputManager()
{
	mKeys[KEYS_QUIT] = KeyInput(ALLEGRO_KEY_ESCAPE, new EventQuit());
}

InputManager::~InputManager()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();

	for (int i = 0; i < KEYS_COUNT; i++)
		delete mKeys[i].mEvent;
}

bool InputManager::init()
{
	if (!al_install_mouse())
		return false;

	if (!al_install_keyboard())
		return false;

	return true;
}

#include <iostream>

void InputManager::update()
{
	al_get_keyboard_state(&mKeyState);
	al_get_mouse_state(&mMouseState);

	//Main Loop for Checking Keys
	for (int i = 0; i < KEYS_COUNT; i++)
	{
		if (al_key_down(&mKeyState, mKeys[i].mAllegroKey))
		{
			if (!mKeys[i].mPressed)
				gpEventSystem->fireEvent(*mKeys[i].mEvent);
			mKeys[i].mPressed = true;
		}
		else
			mKeys[i].mPressed = false;
	}
}