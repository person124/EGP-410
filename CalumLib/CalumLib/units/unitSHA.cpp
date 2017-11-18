#include "unitSHA.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

const std::string COLOR_NAME[SHA_COLOR_COUNT] = 
{
	"blue",
	"red",
	"yellow"
};

UnitSHA::UnitSHA(SHAColor color) : Unit("sha_front")
{
	mpAniBase = Game::pInstance->getAnimationManager()->get("sha_color_" + COLOR_NAME[color]);

	mpAniFear = Game::pInstance->getAnimationManager()->get("sha_fear");

	mAniScale = 3;
}

UnitSHA::~UnitSHA()
{
	//Unit::~Unit();
	delete mpAniBase;
	delete mpAniFear;
}

void UnitSHA::update(double dt)
{
	Unit::update(dt);
}

void UnitSHA::draw()
{
	Game::pInstance->getGraphics()->drawOffset(mPos.x, mPos.y, mpAniBase->getCurrent(), mAniScale);
	Unit::draw();
}