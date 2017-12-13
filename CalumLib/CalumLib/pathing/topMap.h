#ifndef TOP_MAP_H
#define TOP_MAP_H

#include "pathing/node.h"

#include "utils/trackable.h"

#include <vector>

class Grid;

class TopMap : public Trackable
{
	public:
		TopMap(Grid* grid);
		~TopMap();

		std::vector<Node*> getPath(int startX, int startY, int goalX, int goalY);
	private:
		int heuristic(int x1, int y1, int x2, int y2);

		bool contains(const std::vector<Node*>& list, Node* node);
		Node* smallest(const std::vector<Node*>& list);
		Node* find(const std::vector<Node*>& list, Node* node);
		Node* find(const std::vector<Node*>& list, int x, int y);
		void remove(std::vector<Node*>&, Node* node);

		Grid* mpGridReference;
};

#endif