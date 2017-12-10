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

	std::vector<Node*> truePath;

	if (*current != goal)
	{
		return truePath;
	}

	std::vector<TopNode*> path;

	//Make the closed version of current
	TopNode* copy = new TopNode(*current);
	current = copy;

	while (*current != *start)
	{
		path.push_back(current);
		remove(closed, current);
		current = find(closed, current->connectX, current->connectY);
	}

	for (unsigned int i = 0; i < closed.size(); i++)
		delete closed.at(i);

	TopNode* startCopy = new TopNode(*start);
	path.push_back(startCopy);

	std::reverse(path.begin(), path.end());

	//Initally add the start node
	truePath.push_back(new Node(startX, startY));

	Node last = pathStartNode(startX, startY, path.at(0), truePath);
	for (unsigned int i = 1; i < path.size() - 1; i++)
		last = pathNode(last, path.at(i), truePath);
	breadthFirst(last.x, last.y, goalX, goalY, truePath);

	return truePath;
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

Node TopMap::pathStartNode(int startX, int startY, TopNode* top, std::vector<Node*>& path)
{
	int direction = nodeToDirection(top);

	return breadthFirstNode(startX, startY, direction, path);
}

Node TopMap::pathNode(const Node& start, TopNode* top, std::vector<Node*>& path)
{
	int direction = nodeToDirection(top);

	return breadthFirstNode(start.x, start.y, direction, path);
}

int TopMap::nodeToDirection(const TopNode* top)
{
	int direction = 0;
	if (top->x < top->connectX)
		direction = left;
	else if (top->x > top->connectX)
		direction = right;
	else if (top->y < top->connectY)
		direction = up;
	else if (top->y > top->connectY)
		direction = down;

	return direction;
}

Node TopMap::breadthFirstNode(int startX, int startY, int direction, std::vector<Node*>& path)
{
	Node goal = Node();

	int baseX = startX / 5;
	int baseY = startY / 5;

	for (int i = 0; i < GC::TOP_MAP_RESOLUTION; i++)
	{
		int checkX1 = baseX;
		int checkX2 = baseX;
		int checkY1 = baseY;
		int checkY2 = baseY;

		//True if doing up or down
		if (direction < left)
		{
			checkX1 += i;
			checkX2 += i;

			//If were going up need the one above
			if (direction == up)
				checkY2 -= 1;
			//If going down need to lower both
			else if (direction == down)
			{
				checkY1 += GC::TOP_MAP_RESOLUTION - 1;
				checkY2 += GC::TOP_MAP_RESOLUTION;
			}
		}
		//True if doing left or right
		else
		{
			checkY1 += i;
			checkY2 += i;

			if (direction == left)
				checkX2 -= 1;
			else if (direction == right)
			{
				checkX1 += GC::TOP_MAP_RESOLUTION - 1;
				checkX2 += GC::TOP_MAP_RESOLUTION;
			}
		}

		if (!mpGridReference->isSolid(checkX1, checkY1) &&
			!mpGridReference->isSolid(checkX2, checkY2))
		{
			goal.x = checkX2;
			goal.y = checkY2;
		}
	}

	//Goal tile gotten
	breadthFirst(startX, startY, goal.x, goal.y, path);
	return goal;
}

void TopMap::breadthFirst(int startX, int startY, int endX, int endY, std::vector<Node*>& path)
{
	int res = GC::TOP_MAP_RESOLUTION;
	int minX = startX / res * res - 1;
	int maxX = startX / res * res + res;
	int minY = startY / res * res - 1;
	int maxY = startY / res * res + res;

	std::vector<Node*> nodes;

	Node* start = new Node(startX, startY);
	Node goal = Node(endX, endY);

	nodes.push_back(start);

	//Dijkstra
	Node* current = NULL;
	while (nodes.size() > 0)
	{
		//Getting the smallest node
		int cost = 0;
		int pos = -1;
		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (nodes.at(i)->estimatedCost == 0 && (pos == -1 || nodes.at(i)->cost < cost))
			{
				pos = i;
				cost = nodes.at(i)->cost;
			}
		}

		if (pos == -1)
			return;

		current = nodes.at(pos);
		current->estimatedCost = 1;

		//Getting the neighborus
		for (int i = 0; i < 4; i++)
		{
			//Get the value of x and y we're checking
			Node* toCheck = NULL;
			int checkX = -1;
			int checkY = -1;
			switch (i)
			{
				case up:
					checkX = current->x;
					checkY = current->y - 1;
					break;
				case down:
					checkX = current->x;
					checkY = current->y + 1;
					break;
				case left:
					checkX = current->x - 1;
					checkY = current->y;
					break;
				case right:
					checkX = current->x + 1;
					checkY = current->y;
					break;
			}

			//Check to make sure the x and y values are within bounds
			if (checkX != goal.x && (checkX <= minX || checkX >= maxX))
				continue;
			if (checkY != goal.y && (checkY <= minY || checkY >= maxY))
				continue;

			//See if the node already exists
			toCheck = dijGet(nodes, checkX, checkY);
			//If it does, update the cost if we have to
			if (toCheck != NULL)
			{
				if (toCheck->cost > current->cost + 1)
				{
					toCheck->connect(*current);
					toCheck->cost = current->cost + 1;
				}
				continue;
			}

			//Otherwise, make the new node
			toCheck = new Node(checkX, checkY);
			toCheck->connect(*current);
			toCheck->cost = current->cost + 1;

			nodes.push_back(toCheck);
		} //End of for loop

		if (*current == goal)
			break;
	} //End of while loop

	std::vector<Node*> tempPath;

	//Make a new vector that contains the newest path
	while (*current != *start)
	{
		tempPath.push_back(current);
		dijRemove(nodes, current);
		current = dijGet(nodes, current->connectX, current->connectY);
	}

	//Delete all the unused nodes
	for (unsigned int i = 0; i < nodes.size(); i++)
		delete nodes.at(i);

	//Reverse the new path so its in the right order
	std::reverse(tempPath.begin(), tempPath.end());

	//Connect the last node in the current path with the first node in the new path
	path.at(path.size() - 1)->connect(*tempPath.at(0));

	//Add the rest of the nodes
	for (int i = 0; i < tempPath.size(); i++)
		path.push_back(tempPath.at(i));
}

Node* TopMap::dijGet(const std::vector<Node*>& list, int x, int y)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		Node* n = list.at(i);
		if (n->x == x && n->y == y)
			return n;
	}

	return NULL;
}

void TopMap::dijRemove(std::vector<Node*>& list, Node* node)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (*list.at(i) == *node)
			list.erase(list.begin() + i);
	}
}