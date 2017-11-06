#include "inputManager.h"

#include "events/eventSystem.h"
#include "events/eventQuit.h"
#include "events/eventClick.h"
#include "events/eventDijkstra.h"

InputManager::InputManager()
{
	mKeys[KEYS_QUIT] = KeyInput(ALLEGRO_KEY_ESCAPE, new EventQuit());

	mKeys[KEYS_DIJKSTRA] = KeyInput(ALLEGRO_KEY_D, new EventDijkstra());
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

void InputManager::update()
{
	al_get_keyboard_state(&mKeyState);
	al_get_mouse_state(&mMouseState);

	//When either mouse button is pressed
	if (mMouseState.buttons & (1 | 2))
	{
		if (!mMousePressed)
		{
			mMousePressed = true;
			MouseButton state = (mMouseState.buttons & 1) ? left_mouse_button : right_mouse_button;
			gpEventSystem->fireEvent(EventClick(mMouseState.x, mMouseState.y, state));
		}
	}
	else
		mMousePressed = false;

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