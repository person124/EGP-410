#include "unit.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"
#include "graphics/sprite.h"

#include "physics/steeringOutput.h"
#include "physics/vector2.h"

Unit::Unit(const char* animString)
{
	mpAnim = Game::pInstance->getAnimationManager()->get(animString);
	mAniScale = 1.0f;

	mPos = Vector2();
}

Unit::~Unit()
{
	if (mpAnim != NULL)
		delete mpAnim;
}

void Unit::update(double dt)
{
	mpAnim->update(dt);
}

void Unit::draw()
{
	Game::pInstance->getGraphics()->drawOffset((int) mPos.x, (int) mPos.y, mpAnim->getCurrent(), mAniScale);
}

bool Unit::isPointInsideUnit(Vector2& point)
{
	float size = (float) mpAnim->getCurrent()->getWidth();

	float x = point.x;
	float y = point.y;

	if (x >= mPos.x - size && x <= mPos.x + size)
		if (y >= mPos.y - size && y <= mPos.y + size)
			return true;
	return false;
}