#include "HUD.h"

#include "EventSystem.h"
#include "EventMouseMove.h"

#include "Game.h"
#include "GameValues.h"
#include "GraphicsSystem.h"

HUD::HUD()
{
	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);

	gpEventSystem->addListener(EVENT_TOGGLE_DEBUG, this);

	mDebugText[MOD_VELOCITY] = "Enemy (V)elocity:";
	mDebugText[MOD_REACTION_RADIUS] = "Reaction (R)adius:";
	mDebugText[MOD_ANGULAR_SPEED] = "(A)ngular Velocity:";

	mVal = gpGame->getValues();
}

HUD::~HUD()
{
}

void HUD::draw()
{
	GRAPHICS_SYSTEM->drawText(mX, mY, mStrMousePos);

	if (mDrawDebug)
	{
		for (int i = 0; i < MOD_NUM_TYPES; i++)
		{
			char c = '-';
			if (mVal->getCurrentSelected() == i)
				c = '>';
			GRAPHICS_SYSTEM->drawText(0, 20 * i, c + mDebugText[i] + mVal->getValueString(i), ALLEGRO_ALIGN_LEFT);
		}
	}
}

void HUD::handleEvent(const Event& theEvent)
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