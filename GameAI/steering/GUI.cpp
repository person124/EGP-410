#include "GUI.h"

#include "EventSystem.h"
#include "EventMouseMove.h"
#include "EventToggleDebug.h"

#include "GameValueTypes.h"

#include "Game.h"
#include "GameValues.h"
#include "GraphicsSystem.h"

GUI::GUI()
{
	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);

	gpEventSystem->addListener(EVENT_TOGGLE_DEBUG, this);

	mVal = gpGame->getValues();
}

GUI::~GUI()
{
}

void GUI::draw()
{
	GRAPHICS_SYSTEM->drawText(mX, mY, mStrMousePos);

	if (mDrawDebug)
	{
		for (int i = 0; i < MOD_NUM_TYPES; i++)
		{
			char c = '-';
			if (mVal->getCurrentSelected() == i)
				c = '>';
			GRAPHICS_SYSTEM->drawText(0, 20 * i, c + MOD_GUI_STRING[i] + mVal->getValueString(i), ALLEGRO_ALIGN_LEFT);
		}
	}
}

void GUI::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MOUSE_MOVE)
	{
		const EventMouseMove& e = static_cast<const EventMouseMove&>(theEvent);

		mX = e.getX();
		mY = e.getY();

		mStrMousePos = std::to_string(mX) + ":" + std::to_string(mY);
	}
	else if (theEvent.getType() == EVENT_TOGGLE_DEBUG)
	{
		mDrawDebug = !mDrawDebug;
	}
}