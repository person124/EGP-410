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
#include "EventPause.h"
#include "EventChangeColor.h"
#include "EventSetColor.h"
#include "EventSave.h"
#include "EventLoad.h"
#include "EventHelp.h"

InputManager::InputManager()
{
	//Close Game
	mKeys[KEYS_ESCAPE] = KeyInput(ALLEGRO_KEY_ESCAPE, new EventQuit());

	//Add Unit
	mKeys[KEYS_F] = KeyInput(ALLEGRO_KEY_F, new EventAddAI(false));
	//Spawn Cluster of 5 Units
	mKeys[KEYS_I] = KeyInput(ALLEGRO_KEY_I, new EventAddAI(true));

	//Delete a Unit
	mKeys[KEYS_D] = KeyInput(ALLEGRO_KEY_D, new EventDeleteAI());
	//Clear ALL Units
	mKeys[KEYS_TAB] = KeyInput(ALLEGRO_KEY_TAB, new EventClearAI());

	//Toggle Debug Menu
	mKeys[KEYS_O] = KeyInput(ALLEGRO_KEY_O, new EventToggleDebug());

	//Modify Value Up
	mKeys[KEYS_MOD_UP] = KeyInput(ALLEGRO_KEY_EQUALS, new EventModify(true));
	//Modify Value Down
	mKeys[KEYS_MOD_DOWN] = KeyInput(ALLEGRO_KEY_MINUS, new EventModify(false));

	//Pause Game
	mKeys[KEYS_SPACE] = KeyInput(ALLEGRO_KEY_SPACE, new EventPause());

	//GUI Color Stuff
	mKeys[KEYS_QUESTION] = KeyInput(ALLEGRO_KEY_SLASH, new EventChangeColor());
	mKeys[KEYS_Z] = KeyInput(ALLEGRO_KEY_Z, new EventSetColor());

	//Toggle Help Screen
	mKeys[KEYS_TILDE] = KeyInput(ALLEGRO_KEY_TILDE, new EventHelp());

	//Setup for handling GameValues
	for (int i = 0; i < MOD_NUM_TYPES; i++)
		mKeys[i + KEYS_COUNT] = KeyInput(MOD_KEYCODES[i], new EventModifyStat((ModifyValues)i));
}

InputManager::~InputManager()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();

	for (int i = 0; i < TOTAL_KEYS; i++)
		delete mKeys[i].mEvent;
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
	for (int i = 0; i < TOTAL_KEYS; i++)
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

	//Checking 'S' and 'L' keys for saving and loading
	if (al_key_down(&mKeyState, ALLEGRO_KEY_LCTRL))
	{
		if (!mCTRL)
		{
			if (al_key_down(&mKeyState, ALLEGRO_KEY_S))
			{
				gpEventSystem->fireEvent(EventSave());
				mCTRL = true;
			}
			else if (al_key_down(&mKeyState, ALLEGRO_KEY_L))
			{
				gpEventSystem->fireEvent(EventLoad());
				mCTRL = true;
			}
		}
	}
	else
		mCTRL = false;

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