#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

#include <allegro5\allegro.h>

#include "EventListener.h"

#include "Phys.h"

const int WALL_SIZE = 50;
const int WALL_BUFFER = 150;

class WallManager : public EventListener
{
	public:
		WallManager();
		~WallManager();

		void draw();

		Collision* checkCollision(Ray& raycast);
		bool isInsideWall(Vector2& pos);

		void handleEvent(const Event& theEvent);
	private:
		Wall* mpWalls;
		int mCount;

		ALLEGRO_COLOR mWallColor;
};

#endif