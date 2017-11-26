#include "unitPhys.h"

#include "game.h"
#include "globalConst.h"

#include "pathing/grid.h"

#include "physics/steeringOutput.h"
#include "physics/weightedBehaviour.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float PI2 = (float)M_PI * 2.0f;

UnitPhys::UnitPhys(const char* animString) : Unit(animString)
{
	mVel = Vector2();

	mpSteer = new SteeringOutput();

	mpBehaviourArray = NULL;
}

UnitPhys::~UnitPhys()
{
	delete mpSteer;
}

void UnitPhys::update(double dt)
{
	Unit::update(dt);

	float t = (float)dt;

	Vector2 tempPos = mPos;
	tempPos += mVel * t + 0.5f * mpSteer->linear * (t * t);
	if (!checkForWalls(tempPos))
		mPos = tempPos;

	mAngle += mRotation * t + 0.5f * mpSteer->angular * (t * t);

	mVel += mpSteer->linear * t;
	mRotation += mpSteer->angular * t;

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

	mpSteer->linear = Vector2(0, 0);
	mpSteer->angular = 0;
}

void UnitPhys::runBehaviours(SteeringOutput*& out)
{
	//Zero out SteeringOutput
	out->linear.x = 0;
	out->linear.y = 0;
	out->angular = 0;

	//Go through the bahviours
	for (int i = 0; i < mBehaviourSize; i++)
	{
		WeightB behav = mpBehaviourArray[i](this);
		out->linear += behav.weight * behav.steering.linear;
		out->angular += behav.weight * behav.steering.angular;
	}
}

void UnitPhys::setMaxBehaviours(int max)
{
	mBehaviourSize = max;
	mpBehaviourArray = new SteeringFunc[max];
	for (int i = 0; i < max; i++)
		mpBehaviourArray[i] = NULL;
}

void UnitPhys::addBehaviour(SteeringFunc func)
{
	int pos = 0;
	for (pos = 0; pos < mBehaviourSize; pos++)
	{
		if (mpBehaviourArray[pos] != NULL)
			break;
	}

	if (pos == mBehaviourSize)
		return;

	mpBehaviourArray[pos] = func;
}

bool UnitPhys::checkForWalls(const Vector2& pos)
{
	float scale = 1.0f / TILE_SIZE;

	if (Game::pInstance->getCurrentGrid()->isSolid(pos.x * scale, pos.y * scale))
		return true;
	if (Game::pInstance->getCurrentGrid()->isSolid((pos.x + TILE_SIZE) * scale, pos.y * scale))
		return true;
	if (Game::pInstance->getCurrentGrid()->isSolid(pos.x * scale, (pos.y + TILE_SIZE) * scale))
		return true;
	if (Game::pInstance->getCurrentGrid()->isSolid((pos.x + TILE_SIZE) * scale, (pos.y + TILE_SIZE) * scale))
		return true;

	return false;
}