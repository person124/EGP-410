#include "pathing.h"

#include "pathing/grid.h"
#include "pathing/pathList.h"

#include <vector>

int pathing::heurDistance(Node* start, Node* goal)
{
	int x = (start->x - goal->x);
	int y = (start->y - goal->y);
	return (int) sqrtf(x * x - y * y);
}

#include <iostream>

std::vector<Node> pathing::aStar(Grid* grid, Node* start, Node* goal, Heuristic heur)
{
	PathList open = PathList(grid);
	PathList closed = PathList(grid);

	Node startNode = Node(start->x, start->y);
	startNode.estimatedCost = heur(start, goal);

	open.add(startNode);

	Node current;
	while (open.size() > 0)
	{
		current = open.smallestEstimate();

		Node* connections = open.connections(current);
		for (int i = 0; i < 4; i++)
		{
			Node endNode = connections[i];
			if (endNode.dummy)
				continue;
			int endNodeCost = current.cost + 1;

			Node endNodeRecord;
			int endNodeHeuristic;
			if (closed.contains(endNode))
			{
				endNodeRecord = closed.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;

				closed.remove(endNode);
				endNodeHeuristic = endNodeRecord.estimatedCost - endNodeCost;
			}
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.cost <= endNodeCost)
					continue;

				endNodeHeuristic = endNodeRecord.estimatedCost - endNodeCost;
			}
			else
			{
				endNodeRecord = Node(endNode);
				endNodeHeuristic = heur(&endNodeRecord, goal);
			}

			endNodeRecord.cost = endNodeCost;
			endNodeRecord.estimatedCost = endNodeCost + endNodeHeuristic;
			endNodeRecord.connect(current);

			if (!open.contains(endNode))
				open.add(endNodeRecord);
		}
		delete[] connections;

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

	while (current != startNode)
	{
		path.push_back(current);
		current = closed.getNode(current.connectX, current.connectY);
	}

	//Add the start node as the program doesn't add it in for some reason
	path.push_back(startNode);

	//reverse the vector
	std::reverse(path.begin(), path.end());
	//return the final path
	return path;
}

std::vector<Node> pathing::dijkstra(Grid* grid, Node* start, Node* goal)
{
	PathList open = PathList(grid);
	PathList closed = PathList(grid);

	Node startNode = Node(start->x, start->y);

	open.add(startNode);

	Node current;
	while (open.size() > 0)
	{
		current = open.smallest();
		if (current == *goal)
			break;

		Node* connections = open.connections(current);
		for (int i = 0; i < 4; i++)
		{
			Node endNode = connections[i];
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
			endNodeRecord.connect(current);

			if (!open.contains(endNodeRecord))
				open.add(endNodeRecord);
		}

		delete[] connections;

		open.remove(current);
		closed.add(current);
	}

	std::vector<Node> path;

	if (current != *goal)
	{
		//path will be empty if this returns
		return path;
	}

	while (current != startNode)
	{
		path.push_back(current);
		current = closed.getNode(current.connectX, current.connectY);
	}

	//Add the start node as the program doesn't add it in for some reason
	path.push_back(startNode);

	//reverse the vector
	std::reverse(path.begin(), path.end());
	return path;
}