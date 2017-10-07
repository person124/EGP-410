#include "Unit.h"

#include "Game.h"
#include "SpriteManager.h"
#include "Phys.h"
#include "Sprite.h"

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
	mpSprite->draw(*buffer, mPos.x, mPos.y, mAngle);
}

void Unit::stop()
{
    mVel = Vector2(0, 0);
    mRotation = 0;
    mSteer.linear = Vector2(0, 0);
    mSteer.angular = 0;
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