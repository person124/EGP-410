#include "UnitSlottable.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"
#include "GraphicsSystem.h"

UnitSlottable::UnitSlottable(SteeringFunc* behaviourArray, int size, int sprite):Unit(sprite)
{
	mpBehaviourArray = behaviourArray;
	mBehaviourSize = size;
}

UnitSlottable::~UnitSlottable()
{
}

void UnitSlottable::update(float dt)
{
	mMaxSpeed = GameValues::value(MOD_NPC_SPEED);

	mSteer = runBehaviours();

	mPos += mVel * dt + 0.5f * mSteer.linear * (dt * dt);
	mAngle += mRotation * dt + 0.5f * mSteer.angular * (dt * dt);

	mVel += mSteer.linear * dt;
	mRotation += mSteer.angular * dt;

	if (mVel.length() > mMaxSpeed)
	{
		mVel.normalize();
		mVel *= mMaxSpeed;
	}

	GRAPHICS_SYSTEM->wrapCoordinates(mPos);

	setAngle(mVel);
}

SteeringOutput UnitSlottable::runBehaviours()
{
	SteeringOutput output;

	for (int i = 0; i < mBehaviourSize; i++)
	{
		WeightB behav = mpBehaviourArray[i](this);
		output.linear += behav.weight * behav.steering.linear;
		output.angular += behav.weight * behav.steering.angular;
	}

	return output;
}