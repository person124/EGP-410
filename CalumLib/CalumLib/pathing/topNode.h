#ifndef TOP_NODE_H
#define TOP_NODE_H

#include "pathing/node.h"

struct TopNode : public Node
{
	TopNode() : Node() {};
	TopNode(int x, int y);

	bool up, down, left, right;

	TopNode& operator=(TopNode& other);
};

#endif