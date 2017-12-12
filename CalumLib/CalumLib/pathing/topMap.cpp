#include "topMap.h"

#include "globalConst.h"

#include "pathing/grid.h"
#include "pathing/nodeList.h"
#include "pathing/topNode.h"

//Simple direction enum for internal usage for breadth first searching
enum Direction
{
	up,
	down,
	left,
	right
};

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

std::vector<Node*> TopMap::getPath(int startX, int startY, int goalX, int goalY)
{
	std::vector<Node*> open, closed;

	Node* start = new Node(startX, startY);
	Node goal = Node(goalX, goalY);

	open.push_back(start);

	Node* current = NULL;
	while (open.size() > 0)
	{
		current = smallest(open);

		if (current == NULL || *current == goal)
			break;

		for (int i = 0; i < 4; i++)
		{
			int cx = current->x;
			int cy = current->y;

			switch (i)
			{
				case up:
					cy--;
					break;
				case down:
					cy++;
					break;
				case left:
					cx--;
					break;
				case right:
					cx++;
					break;
			}

			if (mpGridReference->isSolid(cx, cy))
				continue;

			Node* connection = find(closed, cx, cy);
			int cost = current->cost + 1;
			int costHeuristic;

			//If connection is in closed
			if (connection != NULL)
			{
				if (connection->cost <= cost)
					continue;

				remove(closed, connection);
				costHeuristic = connection->estimatedCost - cost;
			}
			else
			{
				connection = find(open, cx, cy);

				//If open contains it
				if (connection != NULL)
				{ 
					if (connection->cost <= cost)
						continue;

					costHeuristic = connection->estimatedCost - cost;
				}
				//If connection hasn't been found yet
				else
				{
					connection = new Node(cx, cy);
					costHeuristic = heuristic(connection->x, connection->y, goal.x, goal.y);
				}
			}

			connection->cost = cost;
			connection->estimatedCost = cost + costHeuristic;
			connection->connect(*current);

			if (find(open, connection) == NULL)
				open.push_back(connection);
		} //end of for loop

		remove(open, current);
		closed.push_back(current);
	} //end of while loop

	std::vector<Node*> path;

	if (*current != goal)
		return path;

	while (*current != *start)
	{
		path.push_back(current);
		
		//Remove that node from closed and open
		remove(closed, current);
		remove(open, current);

		current = find(closed, current->connectX, current->connectY);
	}

	//Add start to the path
	remove(closed, start);
	remove(open, start);
	path.push_back(start);

	//Delete all the unused nodes
	for (unsigned int i = 0; i < open.size(); i++)
		delete open.at(i);
	for (unsigned int i = 0; i < closed.size(); i++)
		delete closed.at(i);

	//Reverse the path
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

	return;
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

bool TopMap::contains(const std::vector<Node*>& list, Node* node)
{
	return find(list, node) != NULL;
}

Node* TopMap::smallest(const std::vector<Node*>& list)
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

Node* TopMap::find(const std::vector<Node*>& list, Node* node)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		Node* temp = list.at(i);
		if (temp->x == node->x && temp->y == node->y)
			return temp;
	}

	return NULL;
}

Node* TopMap::find(const std::vector<Node*>& list, int x, int y)
{
	Node node = Node(x, y);
	return find(list, &node);
}

void TopMap::remove(std::vector<Node*>& list, Node* node)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		Node* temp = list.at(i);
		if (temp->x == node->x && temp->y == node->y)
		{
			list.erase(list.begin() + i);
			return;
		}
	}
}