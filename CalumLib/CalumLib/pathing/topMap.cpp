#include "topMap.h"

#include "globalConst.h"

#include "pathing/grid.h"
#include "pathing/nodeList.h"

int min(int var1, int var2)
{
	if (var1 <= var2)
		return var1;
	return var2;
}

TopMap::TopMap(Grid* grid)
{
	mpGridReference = grid;

	mWidth = grid->getWidth() / GC::TOP_MAP_RESOLUTION;
	mHeight = grid->getHeight() / GC::TOP_MAP_RESOLUTION;

	if (grid->getWidth() % GC::TOP_MAP_RESOLUTION != 0)
		mWidth++;
	if (grid->getHeight() % GC::TOP_MAP_RESOLUTION != 0)
		mHeight++;

	mpNodes = NULL;
}

TopMap::~TopMap()
{
	if (mpNodes != NULL)
		delete[] mpNodes;
}

std::vector<TopNode*> TopMap::getPath(int startX, int startY, int goalX, int goalY)
{
	std::vector<TopNode*> open, closed;

	TopNode* start = getNodeRaw(startX, startY);
	Node goal = Node(goalX / GC::TOP_MAP_RESOLUTION, goalY / GC::TOP_MAP_RESOLUTION);

	open.push_back(start);

	TopNode* current = NULL;
	int cx, cy; //Current x and y
	while (open.size() > 0)
	{
		current = smallest(open);

		if (*current == goal)
			break;

		cx = current->x;
		cy = current->y;

		TopNode* connection;
		for (int i = 0; i < 4; i++)
		{
			connection = NULL;
			//Set connection to either up down left right
			//as needed
			switch (i)
			{
			case 0:
				if (current->up)
					connection = getNode(cx, cy - 1);
				break;
			case 1:
				if (current->down)
					connection = getNode(cx, cy + 1);
				break;
			case 2:
				if (current->left)
					connection = getNode(cx - 1, cy);
				break;
			case 3:
				if (current->right)
					connection = getNode(cx + 1, cy);
				break;
			default:
				break;
			}

			if (connection == NULL)
				continue;

			int nodeCost = current->cost + 1;
			int nodeCostHeuristic;

			if (contains(closed, connection))
			{
				TopNode* record = find(closed, connection);

				if (record->cost <= nodeCost)
					continue;

				remove(closed, record);
				nodeCostHeuristic = record->estimatedCost - nodeCost;
				delete record;
			}
			else if (contains(open, connection))
			{
				TopNode* record = find(open, connection);

				if (record->cost <= nodeCost)
					continue;

				nodeCostHeuristic = record->estimatedCost - nodeCost;
			}
			else
				nodeCostHeuristic = heuristic(connection->x, connection->y, goal.x, goal.y);

			connection->cost = nodeCost;
			connection->estimatedCost = nodeCost + nodeCostHeuristic;
			connection->connect(*current);

			if (!contains(open, connection))
				open.push_back(connection);
		} // end of the for loop

		remove(open, current);
		TopNode* copy = new TopNode(*current);
		closed.push_back(copy);
	} //end of the while loop

	std::vector<TopNode*> path;

	if (*current != goal)
	{
		return path;
	}

	//Make the closed version of current
	TopNode* copy = new TopNode(*current);
	current = copy;

	while (*current != *start)
	{
		path.push_back(current);
		remove(closed, current);
		current = find(closed, current->connectX, current->connectY);
	}

	TopNode* startCopy = new TopNode(*start);
	path.push_back(startCopy);

	std::reverse(path.begin(), path.end());

	return path;
}

void TopMap::generateNodes()
{
	mpNodes = new TopNode[mWidth * mHeight];

	for (int yp = 0; yp < mHeight; yp++)
		for (int xp = 0; xp < mWidth; xp++)
		{
			int pos = xp + yp * mWidth;
			TopNode node = TopNode(xp, yp);

			int x = xp * 5;
			int y = yp * 5;

			int xDist = min(GC::TOP_MAP_RESOLUTION, mpGridReference->getWidth() - x);
			int yDist = min(GC::TOP_MAP_RESOLUTION, mpGridReference->getHeight() - y);
			
			if (yp == 0)
				node.up = false;
			if (xp == 0)
				node.left = false;

			//Test Up
			if (yp == 0)
				node.up = false;
			else
			{
				for (int i = 0; i < xDist; i++)
				{
					//Check node and node above to see if both non solid
					if (!mpGridReference->isSolid(x + i, y) &&
						!mpGridReference->isSolid(x + i, y - 1))
					{
						node.up = true;
						break;
					}
				}
			}

			//Test Down
			if (yp == mHeight - 1)
				node.down = false;
			else
			{
				int yVal = y + GC::TOP_MAP_RESOLUTION;

				for (int i = 0; i < xDist; i++)
				{
					if (!mpGridReference->isSolid(x + i, yVal) &&
						!mpGridReference->isSolid(x + i, yVal + 1))
					{
						node.down = true;
						break;
					}
				}
			}
			
			//Test Left
			if (xp == 0)
				node.left = false;
			else
			{
				for (int i = 0; i < yDist; i++)
				{
					if (!mpGridReference->isSolid(x, y + i) &&
						!mpGridReference->isSolid(x - 1, y + i))
					{
						node.left = true;
						break;
					}
				}
			}

			//Test Right
			if (xp == mWidth - 1)
				node.right = false;
			else
			{
				int xVal = x + GC::TOP_MAP_RESOLUTION;

				for (int i = 0; i < yDist; i++)
				{
					if (!mpGridReference->isSolid(xVal, y + i) &&
						!mpGridReference->isSolid(xVal + 1, y + i))
					{
						node.right = true;
						break;
					}
				}
			}

			mpNodes[pos] = node;
		}
}

TopNode* TopMap::getNode(int x, int y)
{
	return &mpNodes[x + y * mWidth];
}

TopNode* TopMap::getNodeRaw(int rawX, int rawY)
{
	int x = rawX / 5;
	int y = rawY / 5;

	if (rawX > (mWidth - 1) * 5)
		x++;
	if (rawY > (mHeight - 1) * 5)
		y++;

	return getNode(x, y);
}

int TopMap::heuristic(int x1, int y1, int x2, int y2)
{
	float x = (float)(x1 - x2);
	float y = (float)(y1 - y2);
	return (int)sqrtf(x * x - y * y);
}

bool TopMap::contains(const std::vector<TopNode*>& list, TopNode* node)
{
	return find(list, node) != NULL;
}

TopNode* TopMap::smallest(const std::vector<TopNode*>& list)
{
	int pos = -1;
	int cost = 0;

	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (pos == -1 || cost < list.at(i)->estimatedCost)
		{
			pos = i;
			cost = list.at(i)->estimatedCost;
		}
	}

	if (pos == -1)
		return NULL;

	return list.at(pos);
}

TopNode* TopMap::find(const std::vector<TopNode*>& list, TopNode* node)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		TopNode* temp = list.at(i);
		if (temp->x == node->x && temp->y == node->y)
			return temp;
	}

	return NULL;
}

TopNode* TopMap::find(const std::vector<TopNode*>& list, int x, int y)
{
	TopNode node = TopNode(x, y);
	return find(list, &node);
}

void TopMap::remove(std::vector<TopNode*>& list, TopNode* node)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		TopNode* temp = list.at(i);
		if (temp->x == node->x && temp->y == node->y)
		{
			list.erase(list.begin() + i);
			return;
		}
	}
}