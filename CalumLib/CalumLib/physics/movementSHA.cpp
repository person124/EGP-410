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
		calculateTracking();
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
		getNewDirection();
	
	moveInDirection();
}

void MovementSHA::moveInDirection()
{
	if (checkForWall(mCurrentDir))
	{
		getNewDirection();
		return;
	}

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

void MovementSHA::getNewDirection()
{
	bool noWall[DIRECTION_COUNT];
	int sum = 0;

	for (int i = 0; i < DIRECTION_COUNT; i++)
	{
		noWall[i] = !checkForWall((Direction)i);
		sum += noWall[i];
	}

	if (sum == 0)
		return;

	int selection = rand() % sum;
	for (int i = 0; i < DIRECTION_COUNT; i++)
	{
		if (selection == i)
		{
			if (noWall[i] && (i != mCurrentDir || sum == 1))
			{
				mCurrentDir = (Direction)i;
				return;
			}
			
			selection++;

			if (selection >= DIRECTION_COUNT)
			{
				selection -= DIRECTION_COUNT;
				i = 0;
			}
		}
	}
}

bool MovementSHA::checkForWall(Direction dir)
{
	Vector2 movement = directionToVelocity(dir) * 5;

	return mpUnit->checkForWallsOffset(movement);
}