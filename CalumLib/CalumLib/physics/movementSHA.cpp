#include "movementSHA.h"

#include "game.h"
#include "globalConst.h"

#include "pathing/pathing.h"

#include "physics/raycast.h"

#include "stateTree/states/statesSHA.h"

#include "units/unitSHA.h"

#include <stdlib.h>
#include <cmath>

const float SPEED = 30;
const float DEGREES_5 = 0.08726646259f;
const float DEGREE = 0.01745329251f;
const float DIR_ANGLES[4] = 
{
	1.57079632679f,
	4.71238898038f,
	3.14159265359f,
	0
};
const float TURN_SPEED = DIR_ANGLES[1] / 3;
const float TWO_PI = 6.28318530718f;
const float PI_2 = DIR_ANGLES[1];
const float DASH_SPEED = 300;

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

Vector2 MovementSHA::getPointInPath(std::vector<Node> path, const Node& start)
{
	Vector2 goal = Vector2();

	Vector2 startVect = Vector2((float)start.x, (float)start.y);

	for (unsigned int i = 0; i < path.size(); i++)
	{
		Vector2 nodeVect = Vector2(path.at(i).x, path.at(i).y);

		if (!RayCast(Game::pInstance->getCurrentGrid(), startVect, nodeVect))
		{
			goal.x = (float)path.at(i - 1).x * TILE_SIZE;
			goal.y = (float)path.at(i - 1).y * TILE_SIZE;
			break;
		}
	}

	goal.x = (float)path.at(path.size() - 1).x * TILE_SIZE;
	goal.y = (float)path.at(path.size() - 1).y * TILE_SIZE;

	return goal;
}

MovementSHA::MovementSHA(UnitSHA* unit)
{
	mCurrentDir = NONE;

	mpUnit = unit;

	mDashing = false;
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

void MovementSHA::calculateTracking()
{
	if (mDashing)
	{
		dash();
		return;
	}

	Vector2 pos = mpUnit->getPosition();
	Vector2 track = mpUnit->getTargetLocation();

	Node start = Node(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
	Node goal = Node(track.x / TILE_SIZE, track.y / TILE_SIZE);

	std::vector<Node> path = pathing::aStar(Game::pInstance->getCurrentGrid(), &start, &goal, pathing::heurDistance);

	Vector2 target = getPointInPath(path, start);

	//Then turn to face and the like
	Vector2 targetVect = target - pos;

	//TODO Normalize the angle
	float targetAngle = targetVect.asAngle();
	float angleInBetween = abs(targetAngle - mpUnit->getAngle());
	if (angleInBetween <= DEGREES_5)
	{
		//Dash forward
		mDashing = true;
		dash();
	}
	else
		turnToFace(targetAngle);
}

void MovementSHA::dash()
{
	Vector2 vel = Vector2::toVector(mpUnit->getAngle());
	vel *= DASH_SPEED;

	mpUnit->setVelocity(vel);

	if (mpUnit->checkForWallsOffset(vel.normal() * 15))
		mDashing = false;
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

	mpUnit->setRotation(copysignf(TURN_SPEED, sign));
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