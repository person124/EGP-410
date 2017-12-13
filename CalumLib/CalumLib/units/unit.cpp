#include "unit.h"

#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"
#include "graphics/sprite.h"

#include "physics/vector2.h"

Unit::Unit(const char* animString)
{
	mpAnim = Game::pInstance->getAnimationManager()->get(animString);
	mAniScale = 1.0f;

	mPos = Vector2();

	mShouldDelete = false;
}

Unit::~Unit()
{
	if (mpAnim != NULL)
		delete mpAnim;
}

void Unit::update(const double& dt)
{
	mpAnim->update(dt);
}

void Unit::draw()
{
	Game::pInstance->getGraphics()->drawOffset(mPos.x, mPos.y, mpAnim->getCurrent(), mAniScale);
}

int Unit::getWidth()
{
	return mpAnim->getCurrent()->getWidth();
}

int Unit::getHeight()
{
	return mpAnim->getCurrent()->getHeight();
}

bool Unit::isPointInsideUnit(Vector2& point)
{
	float width = (float)getWidth();
	float height = (float)getHeight();

	float x = point.x;
	float y = point.y;

	if (x >= mPos.x && x <= mPos.x + width)
		if (y >= mPos.y && y <= mPos.y + height)
			return true;

	return false;
}

bool Unit::isUnitTouching(Unit* otherUnit)
{
	Vector2 thisMin = mPos;
	Vector2 thisMax = thisMin;
	thisMax.x += getWidth();
	thisMax.y += getHeight();

	Vector2 otherMin = otherUnit->getPosition();
	Vector2 otherMax = otherMin;
	otherMax.x += otherUnit->getWidth();
	otherMax.y += otherUnit->getHeight();

	if (thisMin.x < otherMax.x &&
		thisMax.x > otherMin.x &&
		thisMin.y < otherMax.y &&
		thisMax.y > otherMin.y)
		return true;

	return false;
}