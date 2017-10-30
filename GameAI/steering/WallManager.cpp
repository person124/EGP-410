#include "WallManager.h"

#include <allegro5\allegro_primitives.h>

#include "Game.h"
#include "GameValues.h"
#include "GraphicsSystem.h"

#include "EventSystem.h"
#include "EventSetColor.h"

WallManager::WallManager()
{
	mCount = 4;
	mpWalls = new Wall[mCount];
	
	//Temp variables for easier readability
	float w = GRAPHICS_SYSTEM->getWidth();
	float h = GRAPHICS_SYSTEM->getHeight();

	mpWalls[0] = Wall(WALL_SIZE, -WALL_BUFFER, w - WALL_SIZE, WALL_SIZE); //Top Wall
	mpWalls[1] = Wall(-WALL_BUFFER, 0, WALL_SIZE, h); //Left Wall
	mpWalls[2] = Wall(w - WALL_SIZE, 0, w + WALL_BUFFER, h); //Right Wall
	mpWalls[3] = Wall(WALL_SIZE, h - WALL_SIZE, w - WALL_SIZE, h + WALL_BUFFER); //Bottom Wall

	gpEventSystem->addListener(EVENT_CHANGE_COLOR, this);
	gpEventSystem->addListener(EVENT_SET_COLOR, this);
	handleEvent(EventSetColor());
}

WallManager::~WallManager()
{
	delete[] mpWalls;
}

void WallManager::draw()
{
	if (GameValues::value(MOD_WALL_ENABLED) == 1)
	{
		for (int i = 0; i < mCount; i++)
			al_draw_rectangle(mpWalls[i].min.x, mpWalls[i].min.y, mpWalls[i].max.x, mpWalls[i].max.y, mWallColor, 2);
	}
}

Collision* WallManager::checkCollision(Ray& raycast)
{
	Collision* col = NULL;

	if (GameValues::value(MOD_WALL_ENABLED) == 1)
	{
		for (int i = 0; i < mCount; i++)
		{
			col = mpWalls[i].checkCollision(raycast);

			if (col != NULL)
			{
				return col;
			}
		}
	}

	return col;
}

bool WallManager::isInsideWall(Vector2& pos)
{
	if (GameValues::value(MOD_WALL_ENABLED) == 1)
		return false;

	for (int i = 0; i < mCount; i++)
	{
		if (mpWalls[i].isInside(pos))
			return true;
	}

	return false;
}

void WallManager::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CHANGE_COLOR)
		mWallColor = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
	else if (theEvent.getType() == EVENT_SET_COLOR)
		mWallColor = al_map_rgb(255, 0, 255);
}