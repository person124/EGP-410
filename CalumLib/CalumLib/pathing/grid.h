#ifndef GRID_H
#define GRID_H

#include "pathing/node.h"
#include "pathing/spawnLocation.h"

#include "utils/trackable.h"

#include <vector>

class Tile;
class Animation;

class Grid : public Trackable
{
	public:
		static Tile* sNullTile;

	public:
		Grid();
		Grid(int width, int height);
		~Grid();

		void draw();
		void drawSolidity();
		void drawSpawnLocations();

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

		std::vector<SpawnLocation>& getSpawnLocations();

		//Setters
		void setID(int pos, int value);
		void setID(int x, int y, int value);

		void setSize(int newWidth, int newHeight);
		void changeHeight(int newHeight);
		void changeWidth(int newWidth);

		void addSpawnLocation(SpawnType type, int x, int y);
		void removeSpawnLocation(int x, int y);
	private:
		int mWidth, mHeight;
		Tile** mpTiles;

		Animation* mpSpawnAni;

		std::vector<SpawnLocation> mSpawnLocations;
};

#endif