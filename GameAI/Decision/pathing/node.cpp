#include "node.h"

Node::Node()
{
	dummy = true;
}

Node::Node(int xPos, int yPos)
{
	dummy = false;

	x = xPos;
	y = yPos;
	cost = 0;
	estimatedCost = 0;
}

Node::Node(const Node& node)
{
	dummy = node.dummy;

	x = node.x;
	y = node.y;
	cost = node.cost;
	estimatedCost = node.estimatedCost;
	connectX = node.connectX;
	connectY = node.connectY;
}

void Node::connect(Node& node)
{
	connectX = node.x;
	connectY = node.y;
}

bool operator==(Node& left, Node& right)
{
	return left.x == right.x && left.y == right.y;
}

bool operator!=(Node& left, Node& right)
{
	return left.x != right.x || left.y != right.y;
}