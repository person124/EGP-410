#ifndef TOP_MAP_H
#define TOP_MAP_H

#include "pathing/node.h"

#include "utils/trackable.h"

#include <vector>

class Grid;
struct TopNode;

class TopMap : public Trackable
{
	public:
		TopMap(Grid* grid);
		~TopMap();

		std::vector<Node*> getPath(int startX, int startY, int goalX, int goalY);
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

		Node pathStartNode(int startX, int startY, TopNode* top, std::vector<Node*>& path);
		Node pathNode(const Node& start, TopNode* top, std::vector<Node*>& path);
		int nodeToDirection(const TopNode* top);
		Node breadthFirstNode(int startX, int startY, int direction, std::vector<Node*>& path);
		void breadthFirst(int startX, int startY, int endX, int endY, std::vector<Node*>& path);
		Node* dijGet(const std::vector<Node*>& list, int x, int y);
		void dijRemove(std::vector<Node*>& list, Node* node);

		Grid* mpGridReference;
		TopNode* mpNodes;

		int mWidth, mHeight;
};

#endif