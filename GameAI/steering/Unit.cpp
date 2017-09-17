#include "Unit.h"

#include "Phys.h"
#include "Sprite.h"

#include <math.h>

Unit::Unit(Sprite* sprite)
{
	//mPos = { 0, 0 };
	//mVel = { 0, 0 };
	mAngle = 0.0f;
	mRotation = 0.0f;

	mpSprite = sprite;
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

void Unit::setAngle(Vector2& vel)
{
	if (vel.length() > 0)
		mAngle = atan2f(vel.y, vel.x);
}