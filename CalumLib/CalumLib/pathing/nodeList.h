#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "utils/trackable.h"

#include <vector>

struct Node;

class NodeList : public Trackable
{
	public:
		NodeList();
		~NodeList();

		void add(Node& node);
		void remove(Node& node);
		bool contains(Node& node);

		Node* smallestEstimate();
		Node* find(int x, int y);

		int size();
	private:
		int findPos(Node* node);

		std::vector<Node*> mNodes;
};

#endif