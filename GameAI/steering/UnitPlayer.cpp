#include "UnitPlayer.h"

#include "EventSystem.h"
#include "EventMouseClick.h"

#include "Game.h"
#include "SpriteManager.h"

UnitPlayer::UnitPlayer():Unit(PLAYER_ICON_SPRITE_ID)
{
	gpEventSystem->addListener(EVENT_MOUSE_CLICK, this);

	setMaxSpeed(100);
}

UnitPlayer::~UnitPlayer()
{
}

void UnitPlayer::update(float dt)
{
	// Move torwards target
	if (mTarget.x == 0 && mTarget.y == 0);
	else
	{
		mVel = mTarget - mPos;
		mVel.normalize();
		mVel *= mMaxSpeed;

		setAngle(mVel);
	}

	// Adjust values
	mPos += mVel * dt;
}

#include <iostream>
#include <math.h>

void UnitPlayer::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MOUSE_CLICK)
	{
		const EventMouseClick& e = static_cast<const EventMouseClick&>(theEvent);

		mTarget.x = e.getX();
		mTarget.y = e.getY();
	}
}