#include "InputManager.h"

#include "EventSystem.h"
#include "EventQuit.h"
#include "EventMouseMove.h"
#include "EventMouseClick.h"
#include "EventAddAI.h"
#include "EventDeleteAI.h"
#include "EventClearAI.h"
#include "EventToggleDebug.h"
#include "EventModify.h"
#include "EventModifyStat.h"

InputManager::InputManager()
{
	//Escape Key
	mKeys[KEYS_ESCAPE] = KeyInput(ALLEGRO_KEY_ESCAPE, EventQuit());

	//Add Seek Unit
	mKeys[KEYS_S] = KeyInput(ALLEGRO_KEY_S, EventAddAI(false));
	//Add Flee Unit
	mKeys[KEYS_F] = KeyInput(ALLEGRO_KEY_F, EventAddAI(true));

	//Delete a Unit
	mKeys[KEYS_D] = KeyInput(ALLEGRO_KEY_D, EventDeleteAI());
	//Clear ALL Units
	mKeys[KEYS_C] = KeyInput(ALLEGRO_KEY_C, EventClearAI());

	//Toggle Debug Menu
	mKeys[KEYS_I] = KeyInput(ALLEGRO_KEY_I, EventToggleDebug());

	//Modify Value Up
	mKeys[KEYS_MOD_UP] = KeyInput(ALLEGRO_KEY_EQUALS, EventModify(true));
	//Modify Value Down
	mKeys[KEYS_MOD_DOWN] = KeyInput(ALLEGRO_KEY_MINUS, EventModify(false));

	//Modify Velocity
	mKeys[KEYS_V] = KeyInput(ALLEGRO_KEY_V, EventModifyStat(MOD_VELOCITY));
	//Modify Radius
	mKeys[KEYS_R] = KeyInput(ALLEGRO_KEY_R, EventModifyStat(MOD_REACTION_RADIUS));
	//Modify Angular Velocity
	mKeys[KEYS_A] = KeyInput(ALLEGRO_KEY_A, EventModifyStat(MOD_ANGULAR_SPEED));
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

	//Main Loop for Checking Keys
	for (int i = 0; i < KEYS_COUNT; i++)
	{
		if (al_key_down(&mKeyState, mKeys[i].mAllegroKey))
		{
			if (!mKeys[i].mPressed)
				gpEventSystem->fireEvent(mKeys[i].mEvent);
			mKeys[i].mPressed = true;
		}
		else
			mKeys[i].mPressed = false;
	}

	//Move Mouse Handler
	if (mMouseX != mMouseState.x || mMouseY != mMouseState.y)
	{
		mMouseX = mMouseState.x;
		mMouseY = mMouseState.y;
		gpEventSystem->fireEvent(EventMouseMove(mMouseX, mMouseY));
	}

	//Click Handler
	if (mMouseState.buttons & 1)
		gpEventSystem->fireEvent(EventMouseClick(mMouseX, mMouseY));
}