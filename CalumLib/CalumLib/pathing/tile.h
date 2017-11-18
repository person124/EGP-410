#ifndef TILE_H
#define TILE_H

#include "utils/trackable.h"

class Animation;
class Sprite;

class Tile : public Trackable
{
	private:
		static Animation* mspTileAnimation;
		static Animation* mspSolidAnimation;
	public:
		Tile(int id = 0);
		~Tile();

		void draw(int x, int y);
		void drawSolidity(int x, int y);

		bool isSolid();
		int getID();

		void setID(int id);
	private:
		Sprite* mpSprite;
		int mID;
		bool mSolid;
};

#endif