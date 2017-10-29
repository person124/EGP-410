#include "MovementFunctions.h"

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"
#include "WallManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <allegro5\allegro_primitives.h>

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

float align(float target, UnitSlottable* unit)
{
	float angular = 0;

	float angularRadius = 0.05f; // ~10 degrees
	float angularSlow = M_PI_4;
	float maxRotation = M_PI_2;
	float timeTotarget = 0.25f;

	float rotation = target - unit->getAngle();

	rotation = clampAngle(rotation);
	float rotationSize = fabsf(rotation);

	if (rotationSize <= angularRadius)
	{
		unit->setRotation(0);
		return angular;
	}

	float targetRotation;
	if (rotationSize >= angularSlow)
		targetRotation = maxRotation;
	else
		targetRotation = maxRotation * rotationSize / angularSlow;

	targetRotation *= rotation / rotationSize;

	angular = targetRotation - unit->getRotation();
	angular /= timeTotarget;

	if (abs(angular) > GameValues::value(MOD_ANGULAR))
		angular = (angular / angular) * GameValues::value(MOD_ANGULAR);

	return angular;
}

SteeringOutput seek(Vector2& target, UnitSlottable* unit, bool flee)
{
	SteeringOutput out;

	if (!flee)
		out.linear = target - unit->getPosition();
	else
		out.linear = unit->getPosition() - target;

	out.linear.normalize();
	out.linear *= GameValues::value(MOD_ACCEL);

	return out;
}

Vector2 arriveVelocity(Vector2& target, UnitSlottable* unit)
{
	Vector2 linear;
	float timeToTarget = 0.25f;
	float maxAccel = GameValues::value(MOD_ACCEL);

	linear = target - unit->getVelocity();
	linear /= timeToTarget;

	if (linear.length() > maxAccel)
	{
		linear.normalize();
		linear *= maxAccel;
	}

	return linear;
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

WeightB slot::wander(UnitSlottable* unit)
{
	float weight = 1;//GameValues::value(MOD_WEIGHT_WANDER);
	
	float wanderOffset = GameValues::value(MOD_WANDER_OFFSET);
	float wanderRadius = GameValues::value(MOD_WANDER_RADIUS);
	float wanderRate = M_PI_4;//GameValues::value(MOD_NPC_WANDER_RATE);

	float currentAngle = unit->getAngle();
	currentAngle += gpGame->getUnitManager()->randomBinomial() * wanderRate;
	float targetAngle = currentAngle + unit->getAngle();

	Vector2 target = unit->getPosition() + (wanderOffset * unit->getAngleAsVector());
	target += wanderRadius * Vector2::toVector(targetAngle);

	if (GameValues::value(MOD_DISPLAY_TIPS) == 2)
		al_draw_filled_circle(target.x, target.y, 2.5f, al_map_rgb(0, 0, 0));

	SteeringOutput steer;
	steer.linear = seek(target, unit, false).linear;

	return WeightB(steer, weight);
}

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

WeightB slot::wallAvoid(UnitSlottable* unit)
{
	SteeringOutput out;
	float weight = 50;

	Ray ray = Ray((Unit*)unit);

	if (ray.length() == 0)
		return WeightB(out, weight);

	ray.normalize();
	ray *= GameValues::value(MOD_WALL_CAST);

	if (GameValues::value(MOD_DISPLAY_TIPS) == 3)
		al_draw_line(ray.origin.x, ray.origin.y, ray.x + ray.origin.x, ray.y + ray.origin.y, al_map_rgb(0, 0, 255), 2);

	//Do collision Detection here.
	Collision* col = NULL;
	col = gpGame->getWallManager()->checkCollision(ray);

	if (col != NULL)
	{
		float dist = GameValues::value(MOD_WALL_SEEK);

		Vector2 target = col->position + col->normal * dist;

		out = seek(target, unit, false);

		if (GameValues::value(MOD_DISPLAY_TIPS) == 3)
		{
			al_draw_line(col->position.x, col->position.y, dist * col->normal.x + col->position.x, dist * col->normal.y + col->position.y, al_map_rgb(0, 255, 0), 2);
			al_draw_filled_circle(target.x, target.y, 3, al_map_rgb(0, 0, 0));
		}

		delete col;
	}

	return WeightB(out, weight);
}

WeightB slot::face(UnitSlottable* unit)
{
	SteeringOutput steer;
	float weight = GameValues::value(MOD_ALIGNMENT);

	float threshold = GameValues::value(MOD_FACE_THRESHOLD);

	float targetAngle;
	int count = 0;

	targetAngle = unit->getVelocity().toAngle();
	count++;

	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		Unit* u = gpGame->getUnitManager()->getUnit(i);
		if (u == unit)
			continue;

		Vector2 direction = u->getPosition() - unit->getPosition();
		float distance = direction.length();

		if (distance <= threshold)
		{
			targetAngle += u->getAngle();
			count++;
		}
	}

	if (count > 1)
		targetAngle /= count;

	if (unit->getVelocity().length() != 0)
		steer.angular = align(targetAngle, unit);

	return WeightB(steer, weight);
}

WeightB slot::matchVelocity(UnitSlottable* unit)
{
	SteeringOutput steer;
	float weight = 1;

	float threshold = GameValues::value(MOD_VELOCITY_THRESHOLD);

	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		Unit* u = gpGame->getUnitManager()->getUnit(i);
		if (u == unit)
			continue;

		Vector2 direction = u->getPosition() - unit->getPosition();
		float distance = direction.length();

		if (distance <= threshold)
		{
			steer.linear += arriveVelocity(u->getVelocity(), unit);
		}
	}

	return WeightB(steer, weight);
}

WeightB slot::seperation(UnitSlottable* unit)
{
	SteeringOutput steer;
	float weight = GameValues::value(MOD_SEPERATION);

	float threshold = GameValues::value(MOD_SEPERATION_THRESHOLD);
	float decay = GameValues::value(MOD_SEPERATION_DECAY) * -1000;
	float maxAcceleration = GameValues::value(MOD_ACCEL);

	if (GameValues::value(MOD_DISPLAY_TIPS) == 5)
		al_draw_circle(unit->getPosition().x, unit->getPosition().y, threshold, al_map_rgb(255, 255, 255), 2);

	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		Unit* u = gpGame->getUnitManager()->getUnit(i);
		if (u == unit)
			continue;

		Vector2 direction = u->getPosition() - unit->getPosition();
		float distance = direction.length();

		if (distance < threshold)
		{
			float strength = fminf(decay / (distance * distance), maxAcceleration);

			direction.normalize();
			steer.linear += strength * direction;
		}
	}

	if (GameValues::value(MOD_DISPLAY_TIPS) == 5)
		al_draw_line(unit->getPosition().x, unit->getPosition().y, unit->getPosition().x + steer.linear.x, unit->getPosition().y + steer.linear.y, al_map_rgb(0, 255, 0), 2);

	return WeightB(steer, weight);
}

WeightB slot::cohesion(UnitSlottable* unit)
{
	SteeringOutput steer;
	float weight = GameValues::value(MOD_COHESION);

	float maxDistance = GameValues::value(MOD_COHESION_DISTANCE);

	if (GameValues::value(MOD_DISPLAY_TIPS) == 4)
		al_draw_circle(unit->getPosition().x, unit->getPosition().y, maxDistance, al_map_rgb(255, 255, 255), 2);

	Vector2 runningTotal;
	int count = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		Unit* u = gpGame->getUnitManager()->getUnit(i);

		Vector2 direction = u->getPosition() - unit->getPosition();
		float distance = direction.length();

		if (distance <= maxDistance)
		{
			runningTotal += u->getPosition();
			count++;
		}
	}

	if (count > 1)
	{
		runningTotal /= count;

		steer = seek(runningTotal, unit, false);

		if (GameValues::value(MOD_DISPLAY_TIPS) == 4)
			al_draw_line(unit->getPosition().x, unit->getPosition().y, runningTotal.x, runningTotal.y, al_map_rgb(0, 255, 0), 2);
	}

	return WeightB(steer, weight);
}