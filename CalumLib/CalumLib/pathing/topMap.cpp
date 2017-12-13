#include "topMap.h"

#include "globalConst.h"

#include "pathing/grid.h"

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
}

TopMap::~TopMap()
{
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
			int costHeuristic = heuristic(cx * GC::TILE_SIZE, cy * GC::TILE_SIZE, goalX, goalY);

			//If connection is in closed
			if (connection != NULL)
			{
				if (connection->cost <= cost)
					continue;

				remove(closed, connection);
				costHeuristic = costHeuristic;
			}
			else
			{
				connection = find(open, cx, cy);

				//If open contains it
				if (connection != NULL)
				{ 
					if (connection->cost <= cost)
						continue;

					costHeuristic = costHeuristic;
				}
				//If connection hasn't been found yet
				else
				{
					connection = new Node(cx, cy);
					costHeuristic = costHeuristic;
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