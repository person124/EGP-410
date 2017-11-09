#ifndef TILE_H
#define TILE_H

#include <Trackable.h>

class Animation;

class Tile : public Trackable
{
	public:
		Tile(bool solid = false);
		~Tile();

		void draw(int x, int y);

		bool isSolid();
		void setSolid(bool value);
	private:
		Animation* mpAnimation;
		bool mSolid;
};

#endif