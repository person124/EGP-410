#ifndef NODE_H
#define NODE_H

struct Node
{
	//Constructors
	Node();
	Node(int xPos, int yPos);
	Node(const Node& node);

	//Misc Function
	void connect(Node& node);

	//Members
	bool dummy;
	int cost, estimatedCost;
	int x, y;
	int connectX, connectY;
};

bool operator==(Node& left, Node& right);
bool operator!=(Node& left, Node& right);

#endif