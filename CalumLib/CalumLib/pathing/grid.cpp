#include "grid.h"

#include "globalConst.h"
#include "game.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "pathing/tile.h"

Tile* Grid::sNullTile = NULL;

Grid::Grid()
{
	mWidth = 3;
	mHeight = 3;

	mpTiles = new Tile*[mWidth * mHeight];
	for (int i = 0; i < getSize(); i++)
	{
		mpTiles[i] = new Tile(i % 2);
	}

	mpSpawnAni = Game::pInstance->getAnimationManager()->get("editor_spawns");
}

Grid::Grid(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mpTiles = new Tile*[mWidth * mHeight];
	for (int i = 0; i < getSize(); i++)
		mpTiles[i] = new Tile(0);

	mpSpawnAni = Game::pInstance->getAnimationManager()->get("editor_spawns");
}

Grid::~Grid()
{
	for (int i = 0; i < getSize(); i++)
		delete mpTiles[i];
	delete[] mpTiles;

	delete mpSpawnAni;
}

void Grid::draw()
{
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			mpTiles[x + y * mWidth]->draw(x, y);
}

void Grid::drawSolidity()
{
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			mpTiles[x + y * mWidth]->drawSolidity(x, y);
}

void Grid::drawSpawnLocations()
{
	for (unsigned int i = 0; i < mSpawnLocations.size(); i++)
	{
		SpawnLocation sl = mSpawnLocations.at(i);
		Game::pInstance->getGraphics()->drawOffset((float)(sl.x * GC::TILE_SIZE), (float)(sl.y * GC::TILE_SIZE), mpSpawnAni->getSprite(sl.type), (float)GC::TILE_SCALE);
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
		return Grid::sNullTile;

	return mpTiles[pos];
}

Tile* Grid::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
		return Grid::sNullTile;
	return getTile(x + y * mWidth);
}

int Grid::getID(int pos)
{
	if (pos < 0 || pos >= getSize())
		return 0;
	return mpTiles[pos]->getID();
}

int Grid::getID(int x, int y)
{
	if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
		return 0;
	return getID(x + y * mWidth);
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

std::vector<SpawnLocation>& Grid::getSpawnLocations()
{
	return mSpawnLocations;
}

void Grid::setID(int pos, int value)
{
	Tile* t = getTile(pos);
	if (t != NULL)
		t->setID(value);
}

void Grid::setID(int x, int y, int value)
{
	Tile* t = getTile(x, y);
	if (t != NULL)
		t->setID(value);
}

void Grid::setSize(int newWidth, int newHeight)
{
	changeHeight(newHeight);
	changeWidth(newWidth);
}

void Grid::changeHeight(int newHeight)
{
	//Check height first
	if (newHeight != mHeight)
	{
		int oldSize = mWidth * mHeight;
		int newSize = mWidth * newHeight;
		Tile** tempSet = new Tile*[newSize];

		//Make height bigger
		if (newHeight > mHeight)
		{
			//Get old data
			for (int i = 0; i < oldSize; i++)
				tempSet[i] = mpTiles[i];

			//Make new data
			for (int i = oldSize; i < newSize; i++)
				tempSet[i] = new Tile(0);
		}
		//Make height smaller
		else if (newHeight < mHeight)
		{
			//Get some of the old data
			for (int i = 0; i < newSize; i++)
				tempSet[i] = mpTiles[i];
			//Delete the rest of the old data
			for (int i = newSize; i < oldSize; i++)
				delete mpTiles[i];
		}

		//Transfer data
		mpTiles = tempSet;
		//Change the height
		mHeight = newHeight;
	}
}

void Grid::changeWidth(int newWidth)
{
	//Check width first
	if (newWidth != mWidth)
	{
		int oldSize = mWidth * mHeight;
		int newSize = newWidth * mHeight;
		Tile** tempSet = new Tile*[newSize];

		//Make it bigger
		if (newWidth > mWidth)
		{
			int tracker = 0;
			for (int i = 0; i < newSize; i++)
			{
				if (i % newWidth == newWidth - 1)
					tempSet[i] = new Tile(0);
				else
				{
					tempSet[i] = mpTiles[tracker];
					tracker++;
				}
			}
		}
		//Make it smaller
		else if (newWidth < mWidth)
		{
			//Tracker is used to keep track of if we've skipped a tile or not
			int tracker = 0;
			for (int i = 0; i < oldSize; i++)
			{
				if (i % mWidth == mWidth - 1)
					delete mpTiles[i];
				else
				{
					tempSet[tracker] = mpTiles[i];
					tracker++;
				}
			}
		}

		//Transfer data
		mpTiles = tempSet;
		//Change the width
		mWidth = newWidth;
	}
}

void Grid::addSpawnLocation(SpawnType type, int x, int y)
{
	mSpawnLocations.push_back(SpawnLocation(type, x, y));
}

void Grid::removeSpawnLocation(int x, int y)
{
	bool done = true;
	do {
		done = true;

		for (unsigned int i = 0; i < mSpawnLocations.size(); i++)
		{
			SpawnLocation sl = mSpawnLocations.at(i);
			if (sl.x == x && sl.y == y)
			{
				mSpawnLocations.erase(mSpawnLocations.begin() + i);
				done = false;
				break;
			}
		}
	} while (!done);
}