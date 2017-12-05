#include "unitPhys.h"

#include "game.h"
#include "globalConst.h"

#include "graphics/animation.h"
#include "graphics/sprite.h"
#include "graphics/graphicsSystem.h"

#include "pathing/grid.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float PI2 = (float)M_PI * 2.0f;

const int COLLISION_BUFFER = 3;

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

void UnitPhys::draw()
{
	Game::pInstance->getGraphics()->drawOffset
	(
		(int)mPos.x,
		(int)mPos.y,
		mpAnim->getCurrent(),
		mAniScale,
		mAngle
	);
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
	static Grid* grid;
	if (grid == NULL)
		grid = Game::pInstance->getCurrentGrid();
	const static float scale = 1.0f / TILE_SIZE;

	int width = (int)(mpAnim->getCurrent()->getWidth() * mAniScale);
	int height = (int)(mpAnim->getCurrent()->getHeight() * mAniScale);

	int x1 = (int)((pos.x + COLLISION_BUFFER) * scale);
	int x2 = (int)((pos.x + width - COLLISION_BUFFER) * scale);
	int y1 = (int)((pos.y + COLLISION_BUFFER) * scale);
	int y2 = (int)((pos.y + height - COLLISION_BUFFER) * scale);

	if ((mVel.x < 0 || mVel.y < 0) && grid->isSolid(x1, y1))
		return true;
	if ((mVel.x > 0 || mVel.y < 0) && grid->isSolid(x2, y1))
		return true;
	if ((mVel.x > 0 || mVel.y > 0) && grid->isSolid(x2, y2))
		return true;
	if ((mVel.x < 0 || mVel.y > 0) && grid->isSolid(x1, y2))
		return true;

	return false;
}

//TODO
//Make this function and checkForWalls not use so much of the same code
//Maybe make another function
bool UnitPhys::checkForWallsOffset(const Vector2& offset)
{
	static Grid* grid;
	if (grid == NULL)
		grid = Game::pInstance->getCurrentGrid();
	const static float scale = 1.0f / TILE_SIZE;

	int width = (int)(mpAnim->getCurrent()->getWidth() * mAniScale);
	int height = (int)(mpAnim->getCurrent()->getHeight() * mAniScale);

	int x1 = (int)((offset.x + mPos.x + COLLISION_BUFFER) * scale);
	int x2 = (int)((offset.x + mPos.x + width - COLLISION_BUFFER) * scale);
	int y1 = (int)((offset.y + mPos.y + COLLISION_BUFFER) * scale);
	int y2 = (int)((offset.y + mPos.y + height - COLLISION_BUFFER) * scale);

	if ((offset.x < 0 || offset.y < 0) && grid->isSolid(x1, y1))
		return true;
	if ((mVel.x > 0 || offset.y < 0) && grid->isSolid(x2, y1))
		return true;
	if ((offset.x > 0 || offset.y > 0) && grid->isSolid(x2, y2))
		return true;
	if ((offset.x < 0 || offset.y > 0) && grid->isSolid(x1, y2))
		return true;

	return false;
}