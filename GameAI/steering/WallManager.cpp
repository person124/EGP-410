#include "WallManager.h"

#include <allegro5\allegro_primitives.h>

#include "Game.h"
#include "GraphicsSystem.h"

WallManager::WallManager()
{
	mCount = 4;
	mpWalls = new Wall[mCount];
	
	//Temp variables for easier readability
	float w = GRAPHICS_SYSTEM->getWidth();
	float h = GRAPHICS_SYSTEM->getHeight();

	mpWalls[0] = Wall(0, 0, w, WALL_SIZE); //Top Wall
	mpWalls[1] = Wall(0, 0, WALL_SIZE, h); //Left Wall
	mpWalls[2] = Wall(w - WALL_SIZE, 0, w, h); //Right Wall
	mpWalls[3] = Wall(0, h - WALL_SIZE, w, h); //Bottom Wall
}

WallManager::~WallManager()
{
	delete[] mpWalls;
}

void WallManager::draw()
{
	for (int i = 0; i < mCount; i++)
		al_draw_rectangle(mpWalls[i].min.x, mpWalls[i].min.y, mpWalls[i].max.x, mpWalls[i].max.y, al_map_rgb(255, 0, 255), 1);
}

Collision* WallManager::checkCollision(Ray& raycast)
{
	Collision* col = NULL;

	for (int i = 0; i < mCount; i++)
	{
		col = mpWalls[i].checkCollision(raycast);

		if (col != NULL)
		{
			return col;
		}
	}

	return col;
}