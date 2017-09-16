// MadeByCalum
#include "InputManager.h"

#include "EventSystem.h"
#include "EventQuit.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

bool InputManager::init()
{
	if (!al_install_keyboard())
		return false;

	if (!al_install_mouse())
		return false;

	return true;
}

void InputManager::update()
{
	al_get_keyboard_state(&mKeyState);
	al_get_mouse_state(&mMouseState);

	if (al_key_down(&mKeyState, ALLEGRO_KEY_ESCAPE))
		gpEventSystem->fireEvent(EventQuit());
}

void InputManager::draw()
{
	//Draw Mouse pos text
}