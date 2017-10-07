#include "MovementFunctions.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"

#include "UnitPlayer.h"

SteeringOutput arrive(Vector2& target, UnitSlottable* unit, bool flee)
{
	//TODO Make this an actuall definition somewhere
	float mTargetRadius = 10;
	float mSlowRadius = 100;
	float mMaxSpeed = 300;
	float mTimeToTarget = 0.5f;
	float mMaxAccel = 100;

	SteeringOutput out;

	Vector2 direction;
	if (!flee)
		direction = target - unit->getPosition();
	else
		direction = unit->getPosition() - target;

	float distance = direction.length();

	if (!flee && distance < mTargetRadius)
	{
		unit->stop();
		//out is still set to default values at this point
		return out;
	}

	float targetSpeed;
	if (distance > mSlowRadius)
		targetSpeed = mMaxSpeed;
	else
		targetSpeed = (mMaxSpeed * distance) / mSlowRadius;

	Vector2 targetVelocity = direction;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	out.linear = targetVelocity - unit->getVelocity();
	out.linear /= mTimeToTarget;

	if (out.linear.length() > mMaxAccel)
	{
		out.linear.normalize();
		out.linear *= mMaxAccel;
	}

	return out;
}

WeightB arriveOrFlee(UnitSlottable* unit, bool flee)
{
	SteeringOutput steer;
	//TODO Make weights customizable
	float weight = 1;

	Vector2 playerPos = gpGame->getUnitManager()->getPlayer()->getPosition();

	if ((playerPos - unit->getPosition()).length() <= gpGame->getValues()->getValue(MOD_REACTION_RADIUS))
	{
		steer = arrive(playerPos, unit, flee);
	}

	return WeightB(steer, weight);
}

WeightB arrivePlayerWithinRange(UnitSlottable* unit)
{
	return arriveOrFlee(unit, false);
}

WeightB fleePlayerWithinRange(UnitSlottable* unit)
{
	return arriveOrFlee(unit, true);
}

WeightB wander(UnitSlottable* unit)
{
	//REMEMBER TO HAVE THIS ONE CONTROL ITS SPEED, AS IN SLOW IT DOWN
	return WeightB(SteeringOutput(), 0);
}