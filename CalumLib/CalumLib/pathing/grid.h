#ifndef GRID_H
#define GRID_H

#include "pathing/node.h"

#include <vector>

#include "utils/trackable.h"

class Tile;

class Grid : public Trackable
{
	public:
		Grid();
		~Grid();

		void draw();

		//Getters
		int getWidth();
		int getHeight();
		int getSize();

		Tile* getTile(int pos);
		Tile* getTile(int x, int y);
		bool isSolid(int pos);
		bool isSolid(int x, int y);

		//Setters
		void setSolid(int pos, bool value);
		void setSolid(int x, int y, bool value);
	private:
		int mWidth, mHeight;
		Tile** mpTiles;

		//Exists to be able to return NULL
		Tile* mpNullTile;
};

#endif