#include "unitSHA.h"

#include "game.h"

#include "events/event.h"
#include "events/eventSystem.h"
#include "events/eventGameOver.h"

#include "gameMode/level.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "physics/movementSHA.h"

#include "stateTree/stateTreeSHA.h"
#include "stateTree/states/statesSHA.h"

#include "units/unitPlayer.h"

#include "utils/timer.h"

const std::string COLOR_NAME[SHA_COLOR_COUNT] = 
{
	"blue",
	"red",
	"yellow"
};

UnitSHA::UnitSHA(float x, float y, SHAColor color, Unit* player) : UnitPhys(("sha_color_" + COLOR_NAME[color]).c_str())
{
	mpPlayerRef = (UnitPlayer*)player;
	mPos.x = x;
	mPos.y = y;
	mSpawn = Vector2(x, y);

	//Animations
	mpAniBase = Game::pInstance->getAnimationManager()->get("sha");

	mpAniFear = Game::pInstance->getAnimationManager()->get("sha_broken");

	mpAniEnraged = Game::pInstance->getAnimationManager()->get("sha_enraged");

	mpAniRespawn = Game::pInstance->getAnimationManager()->get("sha_respawn");

	mpAniORA = Game::pInstance->getAnimationManager()->get("ora");

	mAniScale = 2;

	//The rest of the data
	mpStateTree = new StateTreeSHA(this);

	mpMovement = new MovementSHA(this);

	gpEventSystem->addListener(EVENT_CANDY_START, this);
	gpEventSystem->addListener(EVENT_CANDY_END, this);
}

UnitSHA::~UnitSHA()
{
	delete mpAniBase;
	delete mpAniFear;
	delete mpAniEnraged;
	delete mpAniRespawn;
	delete mpAniORA;

	delete mpStateTree;

	delete mpMovement;
}

void UnitSHA::update(double dt)
{
	mpAniBase->update(dt);
	mpAniEnraged->update(dt);

	mpStateTree->update(dt);

	if (mpStateTree->getID() == shaFleeing)
		mpAniORA->update(dt);

	if (isUnitTouching(mpPlayerRef))
	{
		if (mpStateTree->getID() != shaDead)
		{
			if (mpPlayerRef->isInvincible())
				mpStateTree->transfer(shaDead);
			else
			{
				EventGameOver e = EventGameOver(((Level*)Game::pInstance->getCurrentMode())->getScore());
				gpEventSystem->fireEvent(e);
			}
		}
	}

	mpMovement->calculateMovement();
	UnitPhys::update(dt);
}

void UnitSHA::draw()
{
	if (mpStateTree->getID() == shaDead)
		Game::pInstance->getGraphics()->drawOffset
		(
			mPos.x,
			mPos.y,
			mpAniRespawn->getCurrent(),
			(float) (mAniScale * (mpStateTree->getTimer()->getElapsedTime() / 10.0)),
			mAngle
		);
	else
	{
		UnitPhys::draw();

		Animation* toRender = mpAniBase;
		if (mpStateTree->getID() == shaTracking)
			toRender = mpAniEnraged;
		else if (mpStateTree->getID() == shaFleeing)
			toRender = mpAniFear;

		Game::pInstance->getGraphics()->drawOffset
		(
			mPos.x,
			mPos.y,
			toRender->getCurrent(),
			mAniScale,
			mAngle
		);
	}

	if (mpStateTree->getID() == shaFleeing)
	{
		Game::pInstance->getGraphics()->drawOffset
		(
			mPos.x - 8,
			mPos.y - 8,
			mpAniORA->getCurrent(),
			(float)3
		);
	}
}

void UnitSHA::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CANDY_START)
	{
		if (mpStateTree->getID() != shaDead)
			mpStateTree->transfer(shaFleeing);
	}
	else if (theEvent.getType() == EVENT_CANDY_END)
	{
		if (mpStateTree->getID() != shaDead)
			mpStateTree->transfer(shaSearching);
		else
		{
			mpStateTree->getTimer()->start();
			mPos = mSpawn;
		}
	}
}

int UnitSHA::getCurrentState()
{
	return mpStateTree->getID();
}