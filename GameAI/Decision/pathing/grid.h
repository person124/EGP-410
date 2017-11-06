#ifndef GRID_H
#define GRID_H

#include <Trackable.h>

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
	private:
		int mWidth, mHeight;
		Tile** mpTiles;
		Tile* mNullTile;
};

#endif