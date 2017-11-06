#include "pathList.h"

#include "pathing/grid.h"
#include "pathing/tile.h"

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
}

Node::Node(const Node& node)
{

	dummy = node.dummy;

	x = node.x;
	y = node.y;
	cost = node.cost;
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

PathList::PathList(Grid* grid)
{
	mGrid = grid;
}

PathList::~PathList()
{
}

void PathList::add(Node node)
{
	mNodes.push_back(node);
}

void PathList::remove(Node node)
{
	int pos = findPos(node);

	if (pos != -1)
		mNodes.erase(mNodes.begin() + pos);
}

bool PathList::contains(Node& node)
{
	for (int i = 0; i < size(); i++)
	{
		if (mNodes.at(i) == node)
			return true;
	}
	return false;
}

int PathList::size()
{
	return mNodes.size();
}

Node& PathList::find(Node& node)
{
	int pos = findPos(node);

	if (pos == -1)
		return Node();

	return mNodes.at(pos);
}

Node& PathList::smallest()
{
	int pos = -1;
	int cost = -1;

	for (int i = 0; i < size(); i++)
	{
		if (cost == -1 || mNodes.at(i).cost < cost)
		{
			pos = i;
			cost = mNodes.at(i).cost;
		}
	}

	return mNodes.at(pos);
}

Node* PathList::connections(Node& node)
{
	Node* nodes = new Node[4];

	Tile* t = mGrid->getTile(node.x + 1, node.y); // Right
	if (t != NULL && !t->isSolid())
		nodes[0] = Node(node.x + 1, node.y);

	t = mGrid->getTile(node.x - 1, node.y); // Left
	if (t != NULL && !t->isSolid())
		nodes[1] = Node(node.x - 1, node.y);

	t = mGrid->getTile(node.x, node.y + 1); // Up
	if (t != NULL && !t->isSolid())
		nodes[2] = Node(node.x, node.y + 1);

	t = mGrid->getTile(node.x, node.y - 1); // Down
	if (t != NULL && !t->isSolid())
		nodes[3] = Node(node.x, node.y - 1);

	return nodes;
}

Node& PathList::getNode(int x, int y)
{
	Node n = Node(x, y);
	return find(n);
}

int PathList::findPos(Node& node)
{
	int pos = -1;
	for (int i = 0; i < size(); i++)
	{
		if (mNodes.at(i) == node)
		{
			pos = i;
			break;
		}
	}

	return pos;
}