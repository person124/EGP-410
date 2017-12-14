#include "movementSHA.h"

#include "game.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "gameMode/level.h"

#include "pathing/node.h"

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

Node MovementSHA::getPointInPath(const std::vector<Node*>& path, const Node& start, unsigned int& startNum)
{
	if (startNum == path.size())
		return *path.at(path.size() - 1);

	Node goal = Node();

	Node* n = NULL;
	for (unsigned int i = startNum; i < path.size(); i++)
	{
		n = path.at(i);

		if (!RayCast(Game::pInstance->getCurrentGrid(), start, *n))
		{
			startNum = i;
			break;
		}
	}

	goal.x = n->x;
	goal.y = n->y ;
	startNum = path.size();

	return goal;
}

MovementSHA::MovementSHA(UnitSHA* unit)
{
	mCurrentDir = NONE;

	mpUnit = unit;

	mDashing = false;
	mpLastPos = NULL;

	mPathCalculated = false;
}

MovementSHA::~MovementSHA()
{
	if (mpLastPos != NULL)
		delete mpLastPos;
	if (mPath.size() > 0)
		for (unsigned int i = 0; i < mPath.size(); i++)
			delete mPath.at(i);
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
			calculateFleeing();
			break;
		case shaTracking:
			calculateTracking();
			break;
		case shaDead:
			mpUnit->setRotation(DIR_ANGLES[0]);
			mDashing = false;
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

void MovementSHA::calculateFleeing()
{
	Node start = Node((int)(mpUnit->getPosition().x * GC::GRID_SCALE), (int)(mpUnit->getPosition().y * GC::GRID_SCALE));
	if (!mPathCalculated || mPath.size() == 0)
	{
		static Level* level = NULL;
		if (level == NULL)
			level = (Level*)Game::pInstance->getCurrentMode();

		start = Node((int)(mpUnit->getPosition().x * GC::GRID_SCALE), (int)(mpUnit->getPosition().y * GC::GRID_SCALE));
		Node goal = Node((int)(mpUnit->getSpawnLocation().x * GC::GRID_SCALE), (int)(mpUnit->getSpawnLocation().y * GC::GRID_SCALE));

		if (mPath.size() > 0)
			for (unsigned int i = 0; i < mPath.size(); i++)
				delete mPath.at(i);

		mPath = level->getPath(start.x, start.y, goal.x, goal.y);

		mLastNode = 0;
		mDashing = false;
		mPathCalculated = true;
	}

	if (mPath.size() == 0)
		return;

	if (!mDashing)
	{
		mTrackPoint = MovementSHA::getPointInPath(mPath, start, mLastNode);
		goToPoint(mTrackPoint);
	}
	else
	{
		if ((mLastNode != mPath.size()) || (start.x == mTrackPoint.x && start.y == mTrackPoint.y))
			mTrackPoint = MovementSHA::getPointInPath(mPath, start, mLastNode);
		goToPoint(mTrackPoint);
	}
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

	//Then turn to face and the like
	Vector2 targetVect = track - pos;

	float targetAngle = targetVect.asAngle();
	float angleInBetween = abs(targetAngle - mpUnit->getAngle());

	if (angleInBetween <= DEGREES_5)
	{
		//Dash forward
		mDashing = true;
		mpUnit->setAngle(targetAngle);
		Game::pInstance->getAudio()->play("sha_dash", false);
		dash();
	}
	else
		turnToFace(targetAngle);
}

void MovementSHA::dash()
{
	if (mpLastPos != NULL && *mpLastPos == mpUnit->getPosition())
	{
		delete mpLastPos;
		mpLastPos = NULL;

		mDashing = false;
		return;
	}

	Vector2 vel = Vector2::toVector(mpUnit->getAngle());
	vel *= DASH_SPEED;

	mpUnit->setVelocity(vel);

	if (mpLastPos == NULL)
		mpLastPos = new Vector2();
	*mpLastPos = mpUnit->getPosition();
}

void MovementSHA::goToPoint(Node& point)
{
	Node current = Node((int)(mpUnit->getPosition().x * GC::GRID_SCALE), (int)(mpUnit->getPosition().y * GC::GRID_SCALE));

	if (point.x == current.x && point.y == current.y)
		return;

	Vector2 difference;
	difference.x = (float)(point.x - current.x);
	difference.y = (float)(point.y - current.y);

	float pointAngle = difference.asAngle();

	float angleBetween = abs(pointAngle - mpUnit->getAngle());

	if (angleBetween <= DEGREES_5)
	{
		mpUnit->setAngle(pointAngle);
		mpUnit->setVelocity(difference.normal() * DASH_SPEED / 5);
		mDashing = true;
	}
	else
		turnToFace(angleBetween);
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
	//Fixes x and y position if stuck in a wall
	float currentX = mpUnit->getPosition().x;
	float currentY = mpUnit->getPosition().y;
	int newPosX = (int)(currentX / GC::TILE_SIZE) * GC::TILE_SIZE;
	int newPosY = (int)(currentY / GC::TILE_SIZE) * GC::TILE_SIZE;

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