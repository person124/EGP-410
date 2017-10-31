#include "Unit.h"

#include "Game.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "GameValues.h"

#include <math.h>

Unit::Unit(int spriteID)
{
	mAngle = 0.0f;
	mRotation = 0.0f;

	mpSprite = gpGame->getSpriteManager()->getSprite(spriteID);
}

Unit::~Unit()
{
}

void Unit::update(float dt)
{
}

void Unit::draw(GraphicsBuffer* buffer)
{
	float size = GameValues::value(MOD_UNIT_SIZE);

	mpSprite->drawScaled(*buffer, mPos.x, mPos.y, size, mAngle);
}

Vector2 Unit::getAngleAsVector()
{
	return Vector2::toVector(mAngle);
}

void Unit::setAngle(Vector2& vel)
{
	if (vel.length() > 0)
		mAngle = atan2f(vel.y, vel.x);
}

void Unit::stop()
{
	mVel = Vector2(0, 0);
	mRotation = 0;
	mSteer.linear = Vector2(0, 0);
	mSteer.angular = 0;
}

bool Unit::isPointInsideUnit(Vector2& point)
{
	float size = GameValues::value(MOD_UNIT_SIZE);

	float x = point.x;
	float y = point.y;

	if (x >= mPos.x - size && x <= mPos.x + size)
		if (y >= mPos.y - size && y <= mPos.y + size)
			return true;
	return false;
}