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
		Grid(int width, int height);
		~Grid();

		void draw();

		//Getters
		int getWidth();
		int getHeight();
		int getSize();

		Tile* getTile(int pos);
		Tile* getTile(int x, int y);
		int getID(int pos);
		int getID(int x, int y);
		bool isSolid(int pos);
		bool isSolid(int x, int y);

		//Setters
		void setID(int pos, int value);
		void setID(int x, int y, int value);
	private:
		int mWidth, mHeight;
		Tile** mpTiles;
};

#endif