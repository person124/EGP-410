#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

#include "Trackable.h"

#include "Phys.h"

const int WALL_SIZE = 50;

class WallManager : public Trackable
{
	public:
		WallManager();
		~WallManager();

		Collision* checkCollision(Ray& raycast);
	private:
		Wall* mpWalls;
		int mCount;
};

#endif