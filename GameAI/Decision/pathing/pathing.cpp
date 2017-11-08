#include "pathing.h"

#include "pathing/grid.h"
#include "pathing/pathList.h"

#include <vector>

// This is a heuristic function. It just returns the raw distance from the goal to the start
int pathing::heurDistance(Node* start, Node* goal)
{
	float x = (float) (start->x - goal->x);
	float y = (float) (start->y - goal->y);
	return (int) sqrtf(x * x - y * y);
}

std::vector<Node> pathing::aStar(Grid* grid, Node* start, Node* goal, Heuristic heur)
{
	//Open and closed node list
	PathList open = PathList(grid);
	PathList closed = PathList(grid);

	//Create the start node and add it to the list
	Node startNode = Node(start->x, start->y);
	startNode.estimatedCost = heur(start, goal);

	open.add(startNode);

	Node current;
	while (open.size() > 0)
	{
		//Get smallest estimated node and its connections
		current = open.smallestEstimate();

		if (current == *goal)
			break;

		Node* connections = open.connections(current);
		for (int i = 0; i < 4; i++)
		{
			//Cycle through the nodes connections
			Node endNode = connections[i];
			//If the node is a dummy then don't bother
			if (endNode.dummy)
				continue;
			int endNodeCost = current.cost + 1;

			Node endNodeRecord;
			int endNodeHeuristic;
			//If closed list contains it, see if we have a better cost, otherwise do nothing
			if (closed.contains(endNode))
			{
				endNodeRecord = closed.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;

				//If we have a better cost then un close that node
				closed.remove(endNode);
				endNodeHeuristic = endNodeRecord.estimatedCost - endNodeCost;
			}
			//If the open list contains the node, update the cost if we have to
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;

				endNodeHeuristic = endNodeRecord.estimatedCost - endNodeCost;
			}
			//Otherwise just create a new node record
			else
			{
				endNodeRecord = Node(endNode);
				endNodeHeuristic = heur(&endNodeRecord, goal);
			}

			//Input the vaules
			endNodeRecord.cost = endNodeCost;
			endNodeRecord.estimatedCost = endNodeCost + endNodeHeuristic;
			endNodeRecord.connect(current);

			//And put it in the open list if its not already
			if (!open.contains(endNode))
				open.add(endNodeRecord);
		}
		delete[] connections;

		//Finally close the current node
		open.remove(current);
		closed.add(current);
	}

	std::vector<Node> path;

	if (current != *goal)
	{
		//path will be empty if this returns
		return path;
	}

	//Cycle through the chain of nodes and add them to the path
	while (current != startNode)
	{
		path.push_back(current);
		current = closed.getNode(current.connectX, current.connectY);
	}

	//Add the start node as the program doesn't add it in
	path.push_back(startNode);

	//reverse the vector
	std::reverse(path.begin(), path.end());
	//return the final path
	return path;
}

std::vector<Node> pathing::dijkstra(Grid* grid, Node* start, Node* goal)
{
	//Open and closed node list
	PathList open = PathList(grid);
	PathList closed = PathList(grid);

	//Create the start node and add it to the list
	Node startNode = Node(start->x, start->y);

	open.add(startNode);

	Node current;
	while (open.size() > 0)
	{
		//Get smallest estimated node and its connections
		current = open.smallest();

		Node* connections = open.connections(current);
		for (int i = 0; i < 4; i++)
		{
			//Cycle through the nodes connections
			Node endNode = connections[i];
			//If the node is a dummy then don't bother
			if (endNode.dummy)
				continue;
			int endNodeCost = current.cost + 1;

			Node endNodeRecord;
			//If closed list contains it do nothing
			if (closed.contains(endNode))
				continue;
			//If the open list contains it, and it has a better cost, than do nothing
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;
			}
			else
				//Other wise make a new node record for it
				endNodeRecord = Node(endNode);

			//Input the values
			endNodeRecord.cost = endNodeCost;
			endNodeRecord.connect(current);

			//Add it to the open list if it isn't already in it
			if (!open.contains(endNodeRecord))
				open.add(endNodeRecord);
		}

		delete[] connections;

		//Finally, remove the current node from the open list and add it to the closed
		open.remove(current);
		closed.add(current);

		if (current == *goal)
			break;
	}

	std::vector<Node> path;

	if (current != *goal)
	{
		//path will be empty if this returns
		return path;
	}

	//Cycle through the chain of nodes and add them to the path
	while (current != startNode)
	{
		path.push_back(current);
		current = closed.getNode(current.connectX, current.connectY);
	}

	//Add the start node as the program doesn't add it in
	path.push_back(startNode);

	//reverse the vector
	std::reverse(path.begin(), path.end());
	return path;
}