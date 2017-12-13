#ifndef MOVEMENT_SHA_H
#define MOVEMENT_SHA_H

#include "pathing/node.h"

#include "physics/vector2.h"

#include "utils/trackable.h"

#include <vector>

class UnitSHA;

enum Direction
{
	NONE = -1,
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	DIRECTION_COUNT
};

class MovementSHA : public Trackable
{
	//Static things
	public:
		static Vector2 directionToVelocity(Direction dir);
		static float directionToAngle(Direction dir);
		static Node getPointInPath(const std::vector<Node*>& path, const Node& start, unsigned int& startNum);

	public:
		MovementSHA(UnitSHA* unit);
		~MovementSHA();

		void calculateMovement();
	private:
		void calculateSearching();
		void calculateFleeing();
		void calculateTracking();

		void dash();

		void goToPoint(Node& point);

		void moveInDirection();
		void turnToFace(float dest);
		void getNewDirection();
		bool checkForWall(Direction dir);

		//Members
		UnitSHA* mpUnit;
		Direction mCurrentDir;
		bool mDashing = false;
		//To be used to detect when should stop dashing
		Vector2* mpLastPos;

		//For fleeing
		bool mPathCalculated;
		std::vector<Node*> mPath;
		Node mTrackPoint;
		unsigned int mLastNode;
};

#endif