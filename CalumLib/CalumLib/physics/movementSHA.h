#ifndef MOVEMENT_SHA_H
#define MOVEMENT_SHA_H

#include "physics/vector2.h"

class UnitSHA;

enum Direction
{
	NONE = -1,
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

struct MovementSHA
{
	//Static things
	public:
		static Direction getNewDirection(Direction oldDirection = NONE);
		static Vector2 directionToVelocity(Direction dir);
		static float directionToAngle(Direction dir);

	public:
		MovementSHA(UnitSHA* unit);
		~MovementSHA();

		void calculateMovement();
	private:
		void calculateSearching();

		void moveInDirection();
		void turnToFace(float dest);

		//Members
		UnitSHA* mpUnit;
		Direction mCurrentDir;
};

#endif