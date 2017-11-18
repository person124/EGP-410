#include "inputManager.h"

#include "events/eventSystem.h"
#include "events/eventClick.h"
#include "events/eventQuit.h"

#include "utils/ioUtils.h"

InputManager::InputManager()
{
	mKeys[KEYS_QUIT] = KeyInput(ALLEGRO_KEY_ESCAPE, new EventQuit());

	mKeys[KEYS_UP] = KeyInput(ALLEGRO_KEY_W, new EventKeypress(KEYS_UP));
	mKeys[KEYS_DOWN] = KeyInput(ALLEGRO_KEY_S, new EventKeypress(KEYS_DOWN));
	mKeys[KEYS_LEFT] = KeyInput(ALLEGRO_KEY_A, new EventKeypress(KEYS_LEFT));
	mKeys[KEYS_RIGHT] = KeyInput(ALLEGRO_KEY_D, new EventKeypress(KEYS_RIGHT));

	mKeys[KEYS_CONFIRM] = KeyInput(ALLEGRO_KEY_ENTER, new EventKeypress(KEYS_CONFIRM));
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