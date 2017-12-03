#include "movementSHA.h"

#include "stateTree/states/statesSHA.h"

#include "units/unitSHA.h"

#include <stdlib.h>
#include <cmath>

const float SPEED = 30;
const float DEGREES_5 = 0.08726646259f;
const float DIR_ANGLES[4] = 
{
	1.57079632679f,
	4.71238898038f,
	3.14159265359f,
	0
};
const float TURN_SPEED = DIR_ANGLES[1];
const float TWO_PI = 6.28318530718f;

MovementSHA::MovementSHA(UnitSHA* unit)
{
	mCurrentDir = NONE;

	mpUnit = unit;
}

MovementSHA::~MovementSHA()
{
}

/*
* Returns a new direction that's not the old one
*/
Direction MovementSHA::getNewDirection(Direction oldDirection)
{
	if (oldDirection == NONE)
		return (Direction)(rand() % 4);

	int num = rand() % 3;

	if (num == oldDirection)
		return RIGHT;

	return (Direction)num;
}

Vector2 MovementSHA::directionToVelocity(Direction dir)
{
	switch (dir)
	{
		case UP:
			return Vector2(0, -1);
		case DOWN:
			return Vector2(0, 1);
		case LEFT:
			return Vector2(-1, 0);
		case RIGHT:
			return Vector2(1, 0);
		default:
			return Vector2(0, 0);
	}
}

float MovementSHA::directionToAngle(Direction dir)
{
	return DIR_ANGLES[(int)dir];
}

void MovementSHA::calculateMovement()
{
	mpUnit->stop();

	switch (mpUnit->getCurrentState())
	{
	case shaSearching:
		calculateSearching();
		break;
	case shaFleeing:
		break;
	case shaTracking:
		break;
	case shaDead:
		mpUnit->setRotation(DIR_ANGLES[0]);
		break;
	default:
		break;
	}
}

#include <iostream>

void MovementSHA::calculateSearching()
{
	//Set a direction if we don't have one
	if (mCurrentDir == NONE)
		mCurrentDir = MovementSHA::getNewDirection();
	
	moveInDirection();
}

void MovementSHA::moveInDirection()
{
	float angleToBe = directionToAngle(mCurrentDir);

	//No division as both vectorDirection and unitAngle have lengths of 1
	float angleInBetween = abs(angleToBe - mpUnit->getAngle());

	if (angleInBetween <= DEGREES_5)
	{
		//Set velocity
		mpUnit->setAngle(angleToBe);
		mpUnit->setVelocity(directionToVelocity(mCurrentDir) * 30);
	}
	else
		turnToFace(angleToBe);
}

void MovementSHA::turnToFace(float dest)
{
	/* Checks to see what is smaller
	 * The distance from the angle to the dest in the
	 * positive or negative direction.
	 * If both distances are the same then it will go
	 * in the degative direction as it doesn't matter.
	 */
	float angle = mpUnit->getAngle();
	if (abs(dest - angle) < ((TWO_PI - dest) + angle))
	{
		//Positive is less, so go positively
		mpUnit->setRotation(TURN_SPEED / 10);
	}
	else
	{
		//Otherwise go negatively
		mpUnit->setRotation(-TURN_SPEED / 10);
	}
}