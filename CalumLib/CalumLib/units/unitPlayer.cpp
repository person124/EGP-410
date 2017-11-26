#include "unitPlayer.h"

#include "game.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"

#include "graphics/animationManager.h"

const int INSTANT_SPEED = 100;

UnitPlayer::UnitPlayer(int x, int y) : UnitDirectional()
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mpAnimFacing[UP] = Game::pInstance->getAnimationManager()->get("player_back");
	mpAnimFacing[DOWN] = Game::pInstance->getAnimationManager()->get("player_front");
	mpAnimFacing[LEFT] = Game::pInstance->getAnimationManager()->get("player_side_flipped");
	mpAnimFacing[RIGHT] = Game::pInstance->getAnimationManager()->get("player_side");
	setAnim(DOWN);

	mAniScale = 1.28f;

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
}

UnitPlayer::~UnitPlayer()
{
}

void UnitPlayer::update(double dt)
{
	UnitDirectional::update(dt);
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
				setAnim(UP);
				break;
			case KEYS_DOWN:
				mVel.y = INSTANT_SPEED;
				mVel.x = 0;
				setAnim(DOWN);
				break;
			case KEYS_LEFT:
				mVel.x = -INSTANT_SPEED;
				mVel.y = 0;
				setAnim(LEFT);
				break;
			case KEYS_RIGHT:
				mVel.x = INSTANT_SPEED;
				mVel.y = 0;
				setAnim(RIGHT);
				break;
			default:
				break;
		}
	}
}