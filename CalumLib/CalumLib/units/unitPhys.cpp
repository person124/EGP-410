#include "unitPhys.h"

#include "game.h"
#include "globalConst.h"

#include "graphics/animation.h"
#include "graphics/sprite.h"

#include "pathing/grid.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float PI2 = (float)M_PI * 2.0f;

UnitPhys::UnitPhys(const char* animString) : Unit(animString)
{
	mVel = Vector2();
}

UnitPhys::~UnitPhys()
{
}

void UnitPhys::update(double dt)
{
	Unit::update(dt);

	float t = (float)dt;

	Vector2 tempPos = mPos;
	tempPos += mVel * t;
	if (!checkForWalls(tempPos))
		mPos = tempPos;

	mAngle += mRotation * t;

	//TODO clamp velocity?

	while (mAngle < 0)
		mAngle += PI2;
	while (mAngle > PI2)
		mAngle -= PI2;
}

Vector2 UnitPhys::getAngleAsVector()
{
	return Vector2::toVector(mAngle);
}

void UnitPhys::setAngle(Vector2& vel)
{
	if (vel.length() != 0)
		mAngle = atan2f(vel.y, vel.x);
}

void UnitPhys::stop()
{
	mVel = Vector2(0, 0);
	mRotation = 0;
}

bool UnitPhys::checkForWalls(const Vector2& pos)
{
	//TODO
	//Fix wal collisions for going up
	static Grid* grid;
	if (grid == NULL)
		grid = Game::pInstance->getCurrentGrid();
	const static float scale = 1.0f / TILE_SIZE;

	int width = mpAnim->getCurrent()->getWidth() * mAniScale;
	int height = mpAnim->getCurrent()->getHeight() * mAniScale;

	int x1 = pos.x * scale;
	int x2 = (pos.x + width) * scale;
	int y1 = pos.y * scale;
	int y2 = (pos.y + height) * scale;

	if ((mVel.x < 0 || mVel.y > 0) && grid->isSolid(x1, y1))
		return true;
	if ((mVel.x > 0 || mVel.y < 0) && grid->isSolid(x2, y1))
		return true;
	if ((mVel.x > 0 || mVel.y > 0) && grid->isSolid(x2, y2))
		return true;
	if ((mVel.x < 0 || mVel.y > 0) && grid->isSolid(x1, y2))
		return true;

	return false;
}