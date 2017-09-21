#include "InputManager.h"

#include "EventSystem.h"
#include "EventQuit.h"
#include "EventMouseClick.h"
#include "EventAddAI.h"
#include "EventDeleteAI.h"

#include "Game.h"
#include <allegro5\allegro.h>

#include <sstream>

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

	if (al_key_down(&mKeyState, ALLEGRO_KEY_A))
		gpEventSystem->fireEvent(EventAddAI(true));

	if (al_key_down(&mKeyState, ALLEGRO_KEY_S))
		gpEventSystem->fireEvent(EventAddAI(false));

	if (al_key_down(&mKeyState, ALLEGRO_KEY_D))
		gpEventSystem->fireEvent(EventDeleteAI());

	if (mMouseState.buttons & 1)
		gpEventSystem->fireEvent(EventMouseClick(mMouseState.x, mMouseState.y));

	std::stringstream ss;
	ss << mMouseState.x << ":" << mMouseState.y;
	mStrMousePos = ss.str();
}

void InputManager::draw()
{
	//Draw Mouse pos text
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mMouseState.x, mMouseState.y, ALLEGRO_ALIGN_CENTER, mStrMousePos.c_str());
}