#ifndef TOP_MAP_H
#define TOP_MAP_H

#include "pathing/topNode.h"

#include "utils/trackable.h"

#include <vector>

class Grid;

class TopMap : public Trackable
{
	public:
		TopMap(Grid* grid);
		~TopMap();

		std::vector<TopNode*> getPath(int startX, int startY, int goalX, int goalY);
		void generateNodes();
	private:
		TopNode* getNode(int x, int y);
		TopNode* getNodeRaw(int rawX, int rawY);
		int heuristic(int x1, int y1, int x2, int y2);

		bool contains(const std::vector<TopNode*>& list, TopNode* node);
		TopNode* smallest(const std::vector<TopNode*>& list);
		TopNode* find(const std::vector<TopNode*>& list, TopNode* node);
		TopNode* find(const std::vector<TopNode*>& list, int x, int y);
		void remove(std::vector<TopNode*>&, TopNode* node);

		Grid* mpGridReference;
		TopNode* mpNodes;

		int mWidth, mHeight;
};

#endif