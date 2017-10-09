#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

#include "Trackable.h"

#include "Phys.h"

const int WALL_SIZE = 50;
const int WALL_BUFFER = 150;

class WallManager : public Trackable
{
	public:
		WallManager();
		~WallManager();

		void draw();

		Collision* checkCollision(Ray& raycast);
		bool isInsideWall(Vector2& pos);
	private:
		Wall* mpWalls;
		int mCount;
};

#endif