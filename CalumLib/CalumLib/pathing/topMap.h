#ifndef TOP_MAP_H
#define TOP_MAP_H

#include "pathing/topNode.h"

class Grid;

class TopMap
{
	public:
		TopMap(Grid* grid);
		~TopMap();

		void generateNodes();
	private:
		Grid* mpGridReference;
		TopNode* mpNodes;

		int mWidth, mHeight;
};

#endif