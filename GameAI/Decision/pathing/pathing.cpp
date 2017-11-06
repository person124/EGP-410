#include "pathing.h"

#include "grid.h"
#include "pathList.h"

#include <vector>

std::vector<Node> pathing::dijkstra(Grid* grid, int startX, int startY, int goalX, int goalY)
{
	PathList open = PathList(grid);
	PathList closed = PathList(grid);

	Node startNode = Node(startX, startY);
	startNode.cost = 0;

	open.add(startNode);

	Node current;
	while (open.size() > 0)
	{
		current = open.smallest();
		if (current.x == goalX && current.y == goalY)
			break;

		Node* connections = open.connections(current);
		for (int i = 0; i < 4; i++)
		{
			Node endNode = connections[i];
			bool test = grid->isSolid(endNode.x, endNode.y);
			if (endNode.dummy)
				continue;
			int endNodeCost = current.cost + 1;

			Node endNodeRecord;
			if (closed.contains(endNode))
				continue;
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;
			}
			else
				endNodeRecord = Node(endNode);

			endNodeRecord.cost = endNodeCost;
			endNodeRecord.connection = new Node(current);

			if (!open.contains(endNode))
				open.add(endNode);
		}

		open.remove(current);
		closed.add(current);
	}

	std::vector<Node> path;

	if (current.x != goalX || current.y != goalY)
	{
		//path will be empty if this returns
		return path;
	}

	while (current != startNode)
	{
		path.push_back(current);
		current = *current.connection;
	}
	return path;
}