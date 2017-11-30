#include "unitPlayer.h"

#include "game.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"

#include "graphics/animationManager.h"

const int INSTANT_SPEED = 100;

UnitPlayer::UnitPlayer(int x, int y) : UnitPhys("player_front")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mAniScale = 1.28f;

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
}

UnitPlayer::~UnitPlayer()
{
}

void UnitPlayer::update(double dt)
{
	UnitPhys::update(dt);
}

void UnitPlayer::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);
		switch (e.getKey())
		{
			case KEYS_UP:
				mVel.y = -INSTANT_SPEED;
				mVel.x = 0;
				break;
			case KEYS_DOWN:
				mVel.y = INSTANT_SPEED;
				mVel.x = 0;
				break;
			case KEYS_LEFT:
				mVel.x = -INSTANT_SPEED;
				mVel.y = 0;
				break;
			case KEYS_RIGHT:
				mVel.x = INSTANT_SPEED;
				mVel.y = 0;
				break;
			default:
				break;
		}
	}
}