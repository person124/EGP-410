#include "grid.h"

#include "../globalConst.h"

#include "tile.h"

Grid::Grid()
{
	mWidth = WIDTH / TILE_SIZE;
	mHeight = HEIGHT / TILE_SIZE;

	mpTiles = new Tile*[mWidth * mHeight];
	for (int i = 0; i < getSize(); i++)
	{
		mpTiles[i] = new Tile(i % 2 == 0);
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
		return mpTiles[0];

	return mpTiles[pos];
}

bool Grid::isSolid(int pos)
{
	return getTile(pos)->isSolid();
}

void Grid::setSolid(int pos, bool value)
{
	getTile(pos)->setSolid(value);
}