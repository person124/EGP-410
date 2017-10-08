#include "UnitPlayer.h"

#include "EventSystem.h"
#include "EventMouseClick.h"

#include "Game.h"
#include "GraphicsSystem.h"
#include "GameValues.h"
#include "SpriteManager.h"

UnitPlayer::UnitPlayer():Unit(PLAYER_ICON_SPRITE_ID)
{
	gpEventSystem->addListener(EVENT_MOUSE_CLICK, this);
	setPosition(GRAPHICS_SYSTEM->getWidth() / 2, GRAPHICS_SYSTEM->getHeight() / 2);
}

UnitPlayer::~UnitPlayer()
{
}

void UnitPlayer::update(float dt)
{
	// Move torwards target
	if (mTarget.x == 0 && mTarget.y == 0)
		return;
	else
	{
		mVel = mTarget - mPos;
		mVel.normalize();
		mVel *= GameValues::value(MOD_PLAYER_SPEED);

		setAngle(mVel);
	}

	// Adjust values
	mPos += mVel * dt;

	if ((mPos - mTarget).length() <= 20)
		stop();
}

void UnitPlayer::stop()
{
	Unit::stop();
	mTarget = Vector2(0, 0);
}

void UnitPlayer::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MOUSE_CLICK)
	{
		const EventMouseClick& e = static_cast<const EventMouseClick&>(theEvent);

		mTarget.x = e.getX();
		mTarget.y = e.getY();
	}
}