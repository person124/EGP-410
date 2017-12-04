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
const float PI_2 = DIR_ANGLES[1];

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

MovementSHA::MovementSHA(UnitSHA* unit)
{
	mCurrentDir = NONE;

	mpUnit = unit;
}

MovementSHA::~MovementSHA()
{
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

void MovementSHA::calculateSearching()
{
	//Set a direction if we don't have one
	if (mCurrentDir == NONE)
		mCurrentDir = MovementSHA::getNewDirection();
	mCurrentDir = UP;
	
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
	 *
	 * Got pseudo-code from:
	 * https://stackoverflow.com/questions/25506470/how-to-get-to-an-angle-choosing-the-shortest-rotation-direction
	 */
	float angle = mpUnit->getAngle();
	float sign = 1;

	if (angle < dest)
	{
		if (abs(angle - dest) < PI_2)
			sign = 1;
		else
			sign = -1;
	}
	else
	{
		if (abs(angle - dest) < PI_2)
			sign = -1;
		else sign = 1;
	}

	mpUnit->setRotation(copysignf(TURN_SPEED / 3, sign));
}