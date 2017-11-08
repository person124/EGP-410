#include "pathList.h"

#include "pathing/grid.h"
#include "pathing/tile.h"

Node PathList::dummyNode = Node();

PathList::PathList(Grid* grid)
{
	mpGrid = grid;
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

Node& PathList::smallestEstimate()
{
	int pos = -1;
	int cost = -1;

	for (int i = 0; i < size(); i++)
	{
		if (cost == -1 || mNodes.at(i).estimatedCost < cost)
		{
			pos = i;
			cost = mNodes.at(i).estimatedCost;
		}
	}

	return mNodes.at(pos);
}

Node& PathList::find(Node& node)
{
	int pos = findPos(node);

	if (pos == -1)
		return PathList::dummyNode;

	return mNodes.at(pos);
}

Node& PathList::getNode(int x, int y)
{
	Node n = Node(x, y);
	return find(n);
}

Node* PathList::connections(Node& node)
{
	Node* nodes = new Node[4];

	Tile* t = mpGrid->getTile(node.x + 1, node.y); // Right
	if (t != NULL && !t->isSolid())
		nodes[0] = Node(node.x + 1, node.y);

	t = mpGrid->getTile(node.x - 1, node.y); // Left
	if (t != NULL && !t->isSolid())
		nodes[1] = Node(node.x - 1, node.y);

	t = mpGrid->getTile(node.x, node.y + 1); // Up
	if (t != NULL && !t->isSolid())
		nodes[2] = Node(node.x, node.y + 1);

	t = mpGrid->getTile(node.x, node.y - 1); // Down
	if (t != NULL && !t->isSolid())
		nodes[3] = Node(node.x, node.y - 1);

	return nodes;
}

int PathList::size()
{
	return mNodes.size();
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