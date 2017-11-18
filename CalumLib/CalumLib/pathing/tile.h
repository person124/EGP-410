#ifndef TILE_H
#define TILE_H

#include "utils/trackable.h"

class Animation;

class Tile : public Trackable
{
	private:
		static Animation* mspSolidAnimation;
	public:
		Tile(int id = 0);
		~Tile();

		void draw(int x, int y);

		bool isSolid();
		int getID();

		void setID(int id);
	private:
		Animation* mpAnimation;
		int mID;
		bool mSolid;
};

#endif