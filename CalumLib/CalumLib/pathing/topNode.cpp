#include "topNode.h"

TopNode::TopNode(int x, int y) : Node(x, y)
{
	up = false;
	down = false;
	left = false;
	right = false;
}

TopNode& TopNode::operator=(TopNode& other)
{
	Node::operator=(other);

	up = other.up;
	down = other.down;
	left = other.left;
	right = other.right;

	return *this;
}