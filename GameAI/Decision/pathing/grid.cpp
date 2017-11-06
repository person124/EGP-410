#include "grid.h"

#include "globalConst.h"
#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/color.h"

#include "events/eventSystem.h"
#include "events/eventClick.h"
#include "events/eventDijkstra.h"

#include "pathing/pathing.h"
#include "pathing/tile.h"

Grid::Grid()
{
	mWidth = WIDTH / TILE_SIZE;
	mHeight = HEIGHT / TILE_SIZE;

	mpTiles = new Tile*[mWidth * mHeight];
	for (int i = 0; i < getSize(); i++)
	{
		mpTiles[i] = new Tile(false);
	}

	mNullTile = NULL;

	gpEventSystem->addListener(EVENT_CLICK, this);
	gpEventSystem->addListener(EVENT_DIJKSTRA, this);

	mStart = new Node(-TILE_SIZE, -TILE_SIZE);
	mGoal = new Node(-TILE_SIZE, -TILE_SIZE);

	mStartBuffer = Game::pInstance->getBufferManager()->get("start");
	mGoalBuffer = Game::pInstance->getBufferManager()->get("goal");

	mDijkstraColor = new Color(255, 0, 0);
	mAStarColor = new Color(0, 119, 255);
}

Grid::~Grid()
{
	for (int i = 0; i < getSize(); i++)
		delete mpTiles[i];
	delete[] mpTiles;

	delete mStart;
	delete mGoal;

	delete mDijkstraColor;
	delete mAStarColor;
}

void Grid::draw()
{
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			mpTiles[x + y * mWidth]->draw(x, y);

	Game::pInstance->getGraphics()->draw(mStart->x * TILE_SIZE, mStart->y * TILE_SIZE, mStartBuffer);
	Game::pInstance->getGraphics()->draw(mGoal->x * TILE_SIZE, mGoal->y * TILE_SIZE, mGoalBuffer);

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
		return mNullTile;

	return mpTiles[pos];
}

Tile* Grid::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
		return mNullTile;
	return getTile(x + y * mWidth);
}

bool Grid::isSolid(int pos)
{
	Tile* t = getTile(pos);
	return t == NULL || t->isSolid();
}

bool Grid::isSolid(int x, int y)
{
	return isSolid(x + y * mWidth);
}

void Grid::setSolid(int pos, bool value)
{
	getTile(pos)->setSolid(value);
}

void Grid::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CLICK)
	{
		const EventClick& e = static_cast<const EventClick&>(theEvent);

		int tileX = e.getX() / TILE_SIZE;
		int tileY = e.getY() / TILE_SIZE;

		if (isSolid(tileX, tileY))
			return;

		if (e.getButton() == left_mouse_button)
		{
			mStart->x = tileX;
			mStart->y = tileY;
		}
		else
		{
			mGoal->x = tileX;
			mGoal->y = tileY;
		}
	}
	else if (theEvent.getType() == EVENT_DIJKSTRA)
	{
		//Do Dijkstra!!!
		mDijkstraPath = pathing::dijkstra(this, mStart, mGoal);
	}
}

void Grid::drawCircle(Node& node, PathUsed type)
{
	int x = node.x * TILE_SIZE + TILE_HALF;
	int y = node.y * TILE_SIZE + TILE_HALF;
	
	Game::pInstance->getGraphics()->drawCircle(x, y, 2, *(type == dijstra ? mDijkstraColor : mAStarColor));
}

void Grid::drawLine(Node& start, Node& end, PathUsed type)
{
	int x1 = start.x * TILE_SIZE + TILE_HALF;
	int y1 = start.y * TILE_SIZE + TILE_HALF;

	int x2 = end.x * TILE_SIZE + TILE_HALF;
	int y2 = end.y * TILE_SIZE + TILE_HALF;

	Game::pInstance->getGraphics()->drawLine(x1, y1, x2, y2, *(type == dijstra ? mDijkstraColor : mAStarColor));
}