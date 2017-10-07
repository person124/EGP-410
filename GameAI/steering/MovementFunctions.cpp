#include "MovementFunctions.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"

#include "UnitPlayer.h"

/*
void UnitDynamic::seek(Vector2& target)
{
mSteer.linear = target - mPos;
mSteer.linear.normalize();
mSteer.linear *= mMaxAccel;

mSteer.angular = 0;
}
*/

SteeringOutput arrive(Vector2& target, UnitSlottable* unit, bool flee)
{
	//TODO Make this an actual definition somewhere
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
	if (!flee && distance > mSlowRadius)
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
	float weight = 0.65f;

	Vector2 playerPos = gpGame->getUnitManager()->getPlayer()->getPosition();

	if ((playerPos - unit->getPosition()).length() <= gpGame->getValues()->getValue(MOD_REACTION_RADIUS))
	{
		steer = arrive(playerPos, unit, flee);
	}

	return WeightB(steer, weight);
}

WeightB slot::arrivePlayerWithinRange(UnitSlottable* unit)
{
	return arriveOrFlee(unit, false);
}

WeightB slot::fleePlayerWithinRange(UnitSlottable* unit)
{
	return arriveOrFlee(unit, true);
}

WeightB slot::wander(UnitSlottable* unit)
{
	float weight = 0.1;
	//TODO FIX WANDER
	float wanderOffset = 300;
	float wanderRadius = 150;
	float wanderRate = 2;
	float maxAcell = 100;

	float currentAngle = unit->getAngle();
	currentAngle += gpGame->getUnitManager()->randomBinomial() * wanderRadius;
	float targetAngle = currentAngle + unit->getAngle();

	Vector2 target = unit->getPosition() + wanderOffset * unit->getAngleAsVector();
	target += wanderRadius * Vector2::toVector(targetAngle);

	unit->setAngle(target);

	SteeringOutput steer;
	steer.linear = maxAcell * unit->getAngleAsVector();

	return WeightB(steer, weight);
}

WeightB slot::avoid(UnitSlottable* unit)
{
	float weight = 0.25f;

	float maxAcell = 200; //Higher for faster avoidance

	float shortestTime = (float) INT_MAX;
	Unit* target = NULL;
	Vector2 targetRelativePos;
	Vector2 targetRelativeVel;
	float targetMinSeperation;
	float targetDistance;

	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		Unit* test = gpGame->getUnitManager()->getUnit(i);
		if (test == unit)
			continue;

		Vector2 relativePos = unit->getPosition() - test->getPosition();
		Vector2 relativeVel = unit->getVelocity() - test->getPosition();
		float relativeSpeed = relativeVel.length();
		float timetoCollision = Vector2::dot(relativePos, relativeVel) / (relativeSpeed * relativeSpeed);
		
		float distance = relativePos.length();
		float minSeperation = distance - relativeSpeed * timetoCollision;

		if (minSeperation > 2 * gpGame->getValues()->getValue(MOD_AVOID_RADIUS))
			continue;
		if (timetoCollision <= 0 || timetoCollision >= shortestTime)
			continue;

		shortestTime = timetoCollision;
		target = test;
		targetRelativePos = relativePos;
		targetRelativeVel = relativeVel;
		targetMinSeperation = minSeperation;
		targetDistance = distance;
	}

	if (target == NULL)
		return WeightB(SteeringOutput(), weight);

	Vector2 relativePosition;
	if (targetMinSeperation <= 0 || targetDistance < 2 * gpGame->getValues()->getValue(MOD_AVOID_RADIUS))
		relativePosition = targetRelativePos;
	else
		relativePosition = targetRelativePos + targetRelativeVel * shortestTime;

	relativePosition.normalize();
	SteeringOutput steer;
	steer.linear = relativePosition * maxAcell;

	return WeightB(steer, weight);
}