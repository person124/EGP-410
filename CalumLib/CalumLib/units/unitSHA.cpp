#include "unitSHA.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "physics/movementSHA.h"

#include "stateTree/StateTreeSHA.h"
#include "stateTree/states/statesSHA.h"

#include "utils/timer.h"

const std::string COLOR_NAME[SHA_COLOR_COUNT] = 
{
	"blue",
	"red",
	"yellow"
};

UnitSHA::UnitSHA(SHAColor color) : UnitPhys("sha")
{
	//Animations
	mpAniBase = Game::pInstance->getAnimationManager()->get("sha_color_" + COLOR_NAME[color]);

	mpAniFear = Game::pInstance->getAnimationManager()->get("sha_broken");

	mpAniEnraged = Game::pInstance->getAnimationManager()->get("sha_enraged");

	mpAniRespawn = Game::pInstance->getAnimationManager()->get("sha_respawn");

	mAniScale = 2;

	//The rest of the data
	mpStateTree = new StateTreeSHA();
}

UnitSHA::~UnitSHA()
{
	delete mpAniBase;
	delete mpAniFear;
	delete mpAniEnraged;
	delete mpAniRespawn;

	delete mpStateTree;
}

void UnitSHA::update(double dt)
{
	mpStateTree->update(dt);

	moveSHA::calculateMovement(this);
	UnitPhys::update(dt);
}

void UnitSHA::draw()
{
	if (mpStateTree->getID() == shaDead)
		Game::pInstance->getGraphics()->drawOffset
		(
			(int)mPos.x,
			(int)mPos.y,
			mpAniRespawn->getCurrent(),
			mAniScale * (mpStateTree->getTimer()->getElapsedTime() / 10),
			mAngle
		);
	else
	{
		Game::pInstance->getGraphics()->drawOffset((int)mPos.x, (int)mPos.y, mpAniBase->getCurrent(), mAniScale, mAngle);
		UnitPhys::draw();
	}
}

int UnitSHA::getCurrentState()
{
	return mpStateTree->getID();
}