#include "grid.h"

#include "globalConst.h"
#include "game.h"

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
		mpTiles[i] = new Tile(false);
	}
}

Grid::~Grid()
{
	for (int i = 0; i < getSize(); i++)
		delete mpTiles[i];
	delete[] mpTiles;
}

void Grid::draw()
{
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			mpTiles[x + y * mWidth]->draw(x, y);
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