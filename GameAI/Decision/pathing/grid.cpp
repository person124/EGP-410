#include "grid.h"

#include "globalConst.h"
#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/color.h"

#include "events/eventSystem.h"
#include "events/eventClick.h"
#include "events/eventDijkstra.h"
#include "events/eventToggleEdit.h"

#include "pathing/pathing.h"
#include "pathing/tile.h"

#include <Timer.h>

Grid::Grid()
{
	mWidth = WINDOW_WIDTH / TILE_SIZE;
	mHeight = WINDOW_HEIGHT / TILE_SIZE;

	mpTiles = new Tile*[mWidth * mHeight];
	for (int i = 0; i < getSize(); i++)
	{
		mpTiles[i] = new Tile(false);
	}

	mpNullTile = NULL;

	gpEventSystem->addListener(EVENT_CLICK, this);
	gpEventSystem->addListener(EVENT_DIJKSTRA, this);
	gpEventSystem->addListener(EVENT_A_STAR, this);
	gpEventSystem->addListener(EVENT_TOGGLE_EDIT, this);

	mpStart = new Node(-1, -1);
	mpGoal = new Node(-1, -1);

	mpStartBuffer = Game::pInstance->getBufferManager()->get("start");
	mpGoalBuffer = Game::pInstance->getBufferManager()->get("goal");

	mpDijkstraColor = new Color(255, 0, 0);
	mpAStarColor = new Color(0, 119, 255);

	mpTimer = new Timer();
}

Grid::~Grid()
{
	for (int i = 0; i < getSize(); i++)
		delete mpTiles[i];
	delete[] mpTiles;

	delete mpStart;
	delete mpGoal;

	delete mpDijkstraColor;
	delete mpAStarColor;

	delete mpTimer;
}

void Grid::draw()
{
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			mpTiles[x + y * mWidth]->draw(x, y);

	Game::pInstance->getGraphics()->draw(mpStart->x * TILE_SIZE, mpStart->y * TILE_SIZE, mpStartBuffer);
	Game::pInstance->getGraphics()->draw(mpGoal->x * TILE_SIZE, mpGoal->y * TILE_SIZE, mpGoalBuffer);

	if (mDijkstraPath.size() > 0)
	{
		drawCircle(mDijkstraPath[0], dijstra);

		for (unsigned int i = 0; i < mDijkstraPath.size(); i++)
		{
			if (i != 0)
				drawLine(mDijkstraPath[i - 1], mDijkstraPath[i], dijstra);

			drawCircle(mDijkstraPath[i], dijstra);
		}
	}

	if (mAStarPath.size() > 0)
	{
		drawCircle(mAStarPath[0], aStar);

		for (unsigned int i = 0; i < mAStarPath.size(); i++)
		{
			if (i != 0)
				drawLine(mAStarPath[i - 1], mAStarPath[i], aStar);

			drawCircle(mAStarPath[i], aStar);
		}
	}

	if (mEditMode)
		Game::pInstance->getGraphics()->writeText(0, 0, *Game::pInstance->getFont(), *mpDijkstraColor, "EDIT MODE");
}

int Grid::getWidth()
{
	return mWidth;
}

int Grid::getHeight()
{
	return mHeight;
}

int Grid::getSize()
{
	return mWidth * mHeight;
}

Tile* Grid::getTile(int pos)
{
	if (pos < 0 || pos >= getSize())
		return mpNullTile;

	return mpTiles[pos];
}

Tile* Grid::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
		return mpNullTile;
	return getTile(x + y * mWidth);
}

bool Grid::isSolid(int pos)
{
	Tile* t = getTile(pos);
	return t == NULL || t->isSolid();
}

bool Grid::isSolid(int x, int y)
{
	Tile* t = getTile(x, y);
	return t == NULL || t->isSolid();
}

void Grid::setSolid(int pos, bool value)
{
	Tile* t = getTile(pos);
	if (t != NULL)
		t->setSolid(value);
}

void Grid::setSolid(int x, int y, bool value)
{
	Tile* t = getTile(x, y);
	if (t != NULL)
		t->setSolid(value);
}

void Grid::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CLICK)
	{
		const EventClick& e = static_cast<const EventClick&>(theEvent);

		int tileX = e.getX() / TILE_SIZE;
		int tileY = e.getY() / TILE_SIZE;

		//If not in edit mode, place start or end
		if (!mEditMode)
		{
			if (isSolid(tileX, tileY))
				return;

			if (e.getButton() == left_mouse_button)
			{
				if (mpGoal->x == tileX && mpGoal->y == tileY)
					return;

				mpStart->x = tileX;
				mpStart->y = tileY;
			}
			else
			{
				if (mpStart->x == tileX && mpStart->y == tileY)
					return;

				mpGoal->x = tileX;
				mpGoal->y = tileY;
			}
		}
		else
		{
			//Otherwise, place the tile
			setSolid(tileX, tileY, e.getButton() == left_mouse_button);
			clearPaths();
			
			if (mpGoal->x == tileX && mpGoal->y == tileY)
				mpGoal->x = -1;
			if (mpStart->x == tileX && mpStart->y == tileY)
				mpStart->x = -1;
		}
	}
	else if (theEvent.getType() == EVENT_DIJKSTRA)
	{
		if (mpStart->x == -1 || mpGoal->x == -1)
			return;

		mpTimer->start();
		mDijkstraPath = pathing::dijkstra(this, mpStart, mpGoal);
		mpTimer->stop();

		printf("Dijkstra took %fms, and %i nodes\n", mpTimer->getElapsedTime(), mDijkstraPath.size());
	}
	else if (theEvent.getType() == EVENT_A_STAR)
	{
		if (mpStart->x == -1 || mpGoal->x == -1)
			return;

		mpTimer->start();
		mAStarPath = pathing::aStar(this, mpStart, mpGoal, pathing::heurDistance);
		mpTimer->stop();

		printf("A*       took %fms, and %i nodes\n", mpTimer->getElapsedTime(), mAStarPath.size());
	}
	else if (theEvent.getType() == EVENT_TOGGLE_EDIT)
	{
		mEditMode = !mEditMode;
		if (mEditMode)
			clearPaths();
	}
}

void Grid::clearPaths()
{
	mDijkstraPath.clear();
	mAStarPath.clear();
}

void Grid::drawCircle(Node& node, PathUsed type)
{
	int x = node.x * TILE_SIZE + TILE_HALF;
	int y = node.y * TILE_SIZE + TILE_HALF + (type == dijstra ? -5 : 5);
	
	Game::pInstance->getGraphics()->drawCircle(x, y, 2, *(type == dijstra ? mpDijkstraColor : mpAStarColor));
}

void Grid::drawLine(Node& start, Node& end, PathUsed type)
{
	int x1 = start.x * TILE_SIZE + TILE_HALF;
	int y1 = start.y * TILE_SIZE + TILE_HALF + (type == dijstra ? -5 : 5);

	int x2 = end.x * TILE_SIZE + TILE_HALF;
	int y2 = end.y * TILE_SIZE + TILE_HALF + (type == dijstra ? -5 : 5);

	Game::pInstance->getGraphics()->drawLine(x1, y1, x2, y2, *(type == dijstra ? mpDijkstraColor : mpAStarColor));
}