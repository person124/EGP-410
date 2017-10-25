#include "MovementFunctions.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"
#include "WallManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

//Maps to range -PI to PI
float clampAngle(float angle)
{
	float output = angle;

	while (output < -M_PI)
		output += M_PI;
	while (output > M_PI)
		output -= M_PI;

	return output;
}

/*
SteeringOutput align(float target, UnitSlottable* unit)
{
	SteeringOutput steer;

	//In Degrees
	float angularRadius = M_PI_4;
	float angularSlow = M_PI_2;
	float maxRotation = M_PI_4;
	float timeTotarget = 0.25f;

	float rotation = target - unit->getAngle();

	rotation = clampAngle(rotation);
	float rotationSize = fabsf(rotation);

	if (rotationSize <= angularRadius)
	{
		unit->setRotation(0);
		return steer;
	}

	float targetRotation;
	if (rotationSize >= angularSlow)
		targetRotation = maxRotation;
	else
		targetRotation = maxRotation * rotationSize / angularSlow;

	targetRotation *= rotation / rotationSize;

	steer.angular = targetRotation - unit->getRotation();
	steer.angular /= timeTotarget;

	if (abs(steer.angular) > GameValues::value(MOD_NPC_ANGULAR))
		steer.angular = GameValues::value(MOD_NPC_ANGULAR);

	return steer;
}
*/

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

/*
WeightB seekOrFlee(UnitSlottable* unit, bool flee)
{
	SteeringOutput steer;
	float weight = GameValues::value(MOD_WEIGHT_SF);

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
*/

/*
WeightB slot::wander(UnitSlottable* unit)
{
	float weight = GameValues::value(MOD_WEIGHT_WANDER);
	
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
*/

/*
WeightB slot::avoid(UnitSlottable* unit)
{
	float weight = GameValues::value(MOD_WEIGHT_AVOID);

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
*/

/*
WeightB slot::wallAvoid(UnitSlottable* unit)
{
	SteeringOutput out;
	float weight = GameValues::value(MOD_WEIGHT_WALL);

	Ray ray = Ray((Unit*)unit);

	if (ray.length() == 0)
		return WeightB(out, weight);

	ray.normalize();
	ray *= GameValues::value(MOD_NPC_WALL_LOOK);

	//Do collision Detection here.
	Collision* col = NULL;
	if (GameValues::value(MOD_WALL_TYPE) > 0)
		col = gpGame->getWallManager()->checkCollision(ray);

	if (col != NULL)
	{
		if (GameValues::value(MOD_WALL_TYPE) == 2)
		{
			Vector2 target = col->position + col->normal * GameValues::value(MOD_NPC_WALL_DIST);
			out = seek(target, unit, false);
		}
		
		if (GameValues::value(MOD_WALL_TYPE) == 1)
		{
			unit->stop();
			out = seek(col->position, unit, true);
		}

		delete col;
	}

	return WeightB(out, weight);
}
*/

/*
WeightB slot::face(UnitSlottable* unit)
{
	SteeringOutput steer;
	float weight = 1;

	if (unit->getVelocity().length() != 0)
	{
		float targetAngle = atan2f(unit->getVelocity().y, unit->getVelocity().x);
		steer = align(targetAngle, unit);
	}

	return WeightB(steer, weight);
}
*/