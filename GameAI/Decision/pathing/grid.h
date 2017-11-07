#ifndef GRID_H
#define GRID_H

#include "events/eventListener.h"
#include "pathing/node.h"

#include <vector>

class Tile;
class GraphicsBuffer;
class Color;

enum PathUsed
{
	dijstra,
	aStar
};

class Grid : public EventListener
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

		//Misc Functions
		void handleEvent(const Event& theEvent);
		void clearPaths();
	private:
		//USed for drawing the paths
		void drawCircle(Node& node, PathUsed type);
		void drawLine(Node& start, Node& end, PathUsed type);

		int mWidth, mHeight;
		Tile** mpTiles;

		//Edit mode bool
		bool mEditMode = false;

		Node* mpStart;
		GraphicsBuffer* mpStartBuffer;
		Node* mpGoal;
		GraphicsBuffer* mpGoalBuffer;

		//Color for draing paths
		Color* mpDijkstraColor;
		Color* mpAStarColor;

		//Path holding variables
		std::vector<Node> mDijkstraPath;
		std::vector<Node> mAStarPath;

		//Exists to be able to return NULL
		Tile* mpNullTile;
};

#endif