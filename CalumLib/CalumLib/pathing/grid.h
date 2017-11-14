#ifndef GRID_H
#define GRID_H

#include "pathing/node.h"

#include "utils/trackable.h"

#include <vector>

class Tile;

class Grid : public Trackable
{
	public:
		static Tile* sNullTile;

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
};

#endif