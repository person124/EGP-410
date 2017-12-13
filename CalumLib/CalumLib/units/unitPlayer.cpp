#include "unitPlayer.h"

#include "game.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"
#include "events/eventCandyStart.h"
#include "events/eventCandyEnd.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "utils/timer.h"

const int INSTANT_SPEED = 100;

enum CandyStage
{
	NONE,
	STARTING,
	IN_PROGRESS
};

UnitPlayer::UnitPlayer(int x, int y) : UnitPhys("player_front")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mXOffset = GC::TILE_SIZE - GC::WINDOW_WIDTH / 2;
	mYOffset = GC::TILE_SIZE - GC::WINDOW_HEIGHT / 2;

	mAniScale = 1.28f;

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
	gpEventSystem->addListener(EVENT_CANDY_START, this);

	mpTimer = new Timer();

	mpORA = Game::pInstance->getAudio()->get("ora");
}

UnitPlayer::~UnitPlayer()
{
	mpORA->stop();
	delete mpTimer;
}

void UnitPlayer::update(const double& dt)
{
	Game::pInstance->getGraphics()->setOffset(mPos.x + mXOffset, mPos.y + mYOffset);

	if (mCandyStage == STARTING)
	{
		if (mpTimer->getElapsedTime() >= 1)
		{
			mpTimer->start();
			mCandyStage = IN_PROGRESS;
		}
		return; //Returns so player cannot move during this time
	}
	else if (mCandyStage == IN_PROGRESS)
	{
		if (mpTimer->getElapsedTime() >= 10)
		{
			mCandyStage = NONE;
			gpEventSystem->fireEvent(EventCandyEnd());
		}
	}

	UnitPhys::update(dt);
}

void UnitPlayer::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CANDY_START)
	{
		mpORA->stop();
		mpORA->play(false);

		mCandyStage = STARTING;
		mpTimer->start();
	}
	else if (theEvent.getType() == EVENT_KEYPRESS)
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