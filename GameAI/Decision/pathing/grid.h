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
		bool isSolid(int pos);

		//Setters
		void setSolid(int pos, bool value);
	private:
		int mWidth, mHeight;
		Tile** mpTiles;
};

#endif