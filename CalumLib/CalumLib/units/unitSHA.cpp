#include "unitSHA.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "physics/movementSHA.h"

#include "stateTree/StateTreeSHA.h"

const std::string COLOR_NAME[SHA_COLOR_COUNT] = 
{
	"blue",
	"red",
	"yellow"
};

UnitSHA::UnitSHA(SHAColor color) : UnitPhys("sha")
{
	mpAniBase = Game::pInstance->getAnimationManager()->get("sha_color_" + COLOR_NAME[color]);

	mpAniFear = Game::pInstance->getAnimationManager()->get("sha_broken");

	mpAniEnraged = Game::pInstance->getAnimationManager()->get("sha_enraged");

	mAniScale = 2;

	mpStateTree = new StateTreeSHA();
}

UnitSHA::~UnitSHA()
{
	delete mpAniBase;
	delete mpAniFear;
	delete mpAniEnraged;

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
	Game::pInstance->getGraphics()->drawOffset((int) mPos.x, (int) mPos.y, mpAniBase->getCurrent(), mAniScale);
	UnitPhys::draw();
}

int UnitSHA::getCurrentState()
{
	return mpStateTree->getID();
}