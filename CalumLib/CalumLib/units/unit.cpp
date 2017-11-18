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
	mVel = Vector2();

	mpSteer = new SteeringOutput();
}

Unit::~Unit()
{
	delete mpSteer;
	delete mpAnim;
}

void Unit::update(double dt)
{
	mpAnim->update(dt);
	//TODO movement update loop
}

void Unit::draw()
{
	Game::pInstance->getGraphics()->drawOffset((int) mPos.x, (int) mPos.y, mpAnim->getCurrent(), mAniScale);
}

Vector2 Unit::getAngleAsVector()
{
	return Vector2::toVector(mAngle);
}

void Unit::setAngle(Vector2& vel)
{
	if (vel.length() != 0)
		mAngle = atan2f(vel.y, vel.x);
}

void Unit::stop()
{
	mVel = Vector2(0,0);
	mRotation = 0;

	mpSteer->linear = Vector2(0, 0);
	mpSteer->angular = 0;
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