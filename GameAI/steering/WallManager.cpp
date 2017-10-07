#include "WallManager.h"

#include "Game.h"
#include "GraphicsSystem.h"

WallManager::WallManager()
{
	mCount = 1;
	mpWalls = new Wall[mCount];
	
	//Temp variables for easier readability
	float w = GRAPHICS_SYSTEM->getWidth();
	float h = GRAPHICS_SYSTEM->getHeight();

	mpWalls[0] = Wall(0, 0, w, WALL_SIZE); //Top Wall
	//mpWalls[1] = Wall(0, 0, WALL_SIZE, h); //Left Wall
	//mpWalls[2] = Wall(w - WALL_SIZE, 0, w, h); //Right Wall
	//mpWalls[3] = Wall(0, h - WALL_SIZE, w, h); //Bottom Wall
}

WallManager::~WallManager()
{
	delete[] mpWalls;
}

#include <iostream>

Collision* WallManager::checkCollision(Ray& raycast)
{
	Collision* output = NULL;

	for (int i = 0; i < mCount; i++)
	{
		Collision* test = mpWalls[i].checkCollision(raycast);
		std::cout << (test != NULL);

		if (test == NULL)
			continue;

		if (output == NULL)
			output = test;
		else
			if (test->size < output->size)
			{
				delete output;
				output = test;
			}
			else
				delete test;
	}
	std::cout << '\n';

	return output;
}