#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "pathing/node.h"

#include "utils/trackable.h"

#include <vector>

class Grid;

class PathList : public Trackable
{
	public:
		static Node sDummyNode;

	public:
		PathList(Grid* grid);
		~PathList();

		//Contents Functions
		void add(Node node);
		void remove(Node node);
		bool contains(Node& node);

		//Funcs that return a node
		Node& smallest();
		Node& smallestEstimate();
		Node& find(Node& node);
		Node& getNode(int x, int y);
		Node* connections(Node& node);

		//Misc
		int size();
	private:
		int findPos(Node& node);

		Grid* mpGrid;
		std::vector<Node> mNodes;
};

#endif