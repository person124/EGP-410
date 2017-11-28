#include "unitSHA.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "physics/movementSHA.h"

const std::string COLOR_NAME[SHA_COLOR_COUNT] = 
{
	"blue",
	"red",
	"yellow"
};

UnitSHA::UnitSHA(SHAColor color) : UnitDirectional()
{
	mpAnimFacing[UP] = Game::pInstance->getAnimationManager()->get("sha_back");
	mpAnimFacing[DOWN] = Game::pInstance->getAnimationManager()->get("sha_front");
	mpAnimFacing[LEFT] = Game::pInstance->getAnimationManager()->get("sha_side_flipped");
	mpAnimFacing[RIGHT] = Game::pInstance->getAnimationManager()->get("sha_side");
	setAnim(DOWN);

	mpAniBase = Game::pInstance->getAnimationManager()->get("sha_color_" + COLOR_NAME[color]);

	mpAniFear = Game::pInstance->getAnimationManager()->get("sha_fear");

	mAniScale = 2;
}

UnitSHA::~UnitSHA()
{
	delete mpAniBase;
	delete mpAniFear;
}

void UnitSHA::update(double dt)
{
	moveSHA::calculateMovement(this);

	UnitDirectional::update(dt);
}

void UnitSHA::draw()
{
	Game::pInstance->getGraphics()->drawOffset((int) mPos.x, (int) mPos.y, mpAniBase->getCurrent(), mAniScale);
	UnitDirectional::draw();
}