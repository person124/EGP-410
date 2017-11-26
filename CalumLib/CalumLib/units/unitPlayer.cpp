#include "unitPlayer.h"

#include "game.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"

#include "graphics/animationManager.h"

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
				mVel.y -= 5;
				break;
			case KEYS_DOWN:
				mVel.y += 5;
				break;
			case KEYS_LEFT:
				mVel.x -= 5;
				break;
			case KEYS_RIGHT:
				mVel.x += 5;
				break;
			default:
				break;
		}
	}
}