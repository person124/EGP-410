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
		Game::pInstance->getGraphics()->drawOffset(sl.x * GC::TILE_SIZE, sl.y * GC::TILE_SIZE, mpSpawnAni->getSprite(sl.type), GC::TILE_SCALE);
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