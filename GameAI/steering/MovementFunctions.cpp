#include "MovementFunctions.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"

#include "UnitPlayer.h"

SteeringOutput seek(Vector2& target, UnitSlottable* unit, bool flee)
{
	SteeringOutput out;

	if (!flee)
		out.linear = target - unit->getPosition();
	else
		out.linear = unit->getPosition() - target;

	out.linear.normalize();
	out.linear *= GameValues::value(MOD_NPC_ACCEL);

	return out;
}

/*
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
*/

WeightB seekOrFlee(UnitSlottable* unit, bool flee)
{
	SteeringOutput steer;
	//TODO Make weights customizable
	float weight = 0.65f;

	Vector2 playerPos = gpGame->getUnitManager()->getPlayer()->getPosition();

	if ((playerPos - unit->getPosition()).length() <= GameValues::value(MOD_NPC_REACT))
	{
		steer = seek(playerPos, unit, flee);
	}

	return WeightB(steer, weight);
}

WeightB slot::seekPlayerWithinRange(UnitSlottable* unit)
{
	return seekOrFlee(unit, false);
}

WeightB slot::fleePlayerWithinRange(UnitSlottable* unit)
{
	return seekOrFlee(unit, true);
}

WeightB slot::wander(UnitSlottable* unit)
{
	float weight = 0.1f;
	
	float wanderOffset = GameValues::value(MOD_NPC_WANDER_CIRCLE);
	float wanderRadius = wanderOffset * 2;
	float wanderRate = GameValues::value(MOD_NPC_WANDER_RATE);

	float currentAngle = unit->getAngle();
	currentAngle += gpGame->getUnitManager()->randomBinomial() * wanderRate;
	float targetAngle = currentAngle + unit->getAngle();

	Vector2 target = unit->getPosition() + wanderOffset * unit->getAngleAsVector();
	target += wanderRadius * Vector2::toVector(targetAngle);

	unit->setAngle(target);

	SteeringOutput steer;
	steer.linear = GameValues::value(MOD_NPC_ACCEL) * unit->getAngleAsVector();

	return WeightB(steer, weight);
}

WeightB slot::avoid(UnitSlottable* unit)
{
	float weight = 0.25f;

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

		if (minSeperation > 2 * GameValues::value(MOD_NPC_AVOID))
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
	if (targetMinSeperation <= 0 || targetDistance < 2 * GameValues::value(MOD_NPC_AVOID))
		relativePosition = targetRelativePos;
	else
		relativePosition = targetRelativePos + targetRelativeVel * shortestTime;

	relativePosition.normalize();
	SteeringOutput steer;
	steer.linear = relativePosition * GameValues::value(MOD_NPC_ACCEL);

	return WeightB(steer, weight);
}