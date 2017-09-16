// MadeByCalum
#include "Unit.h"

#include "Sprite.h"

Unit::Unit()
{
	mPos = { 0, 0 };
	mVel = { 0, 0 };
	mAngle = 0.0f;
	mRotation = 0.0f;
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