#include "nodeList.h"

#include "pathing/node.h"

NodeList::NodeList()
{
}

NodeList::~NodeList()
{
}

void NodeList::add(Node& node)
{
	mNodes.push_back(&node);
}

void NodeList::remove(Node& node)
{
	int pos = findPos(&node);

	if (pos != -1)
		mNodes.erase(mNodes.begin() + pos);
}

bool NodeList::contains(Node& node)
{
	for (int i = 0; i < size(); i++)
	{
		if (mNodes.at(i) == &node)
			return true;
	}

	return false;
}

Node* NodeList::smallestEstimate()
{
	int pos = -1;
	int cost = 10000000;

	for (int i = 0; i < size(); i++)
	{
		if (mNodes.at(i)->estimatedCost < cost)
		{
			pos = i;
			cost = mNodes.at(i)->estimatedCost;
		}
	}

	return mNodes.at(pos);
}

Node* NodeList::find(int x, int y)
{
	int pos = -1;

	for (int i = 0; i < size(); i++)
	{
		Node* node = mNodes.at(i);
		if (node->x == x && node->y == y)
		{
			pos = i;
			break;
		}
	}

	if (pos == -1)
		return NULL;

	return mNodes.at(pos);
}

int NodeList::size()
{
	return mNodes.size();
}

int NodeList::findPos(Node* node)
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