#ifndef PATHING_H
#define PATHING_H

#include "pathing/pathList.h"

#include <vector>

class Grid;

typedef int(Heuristic)(Node* start, Node* goal);

namespace pathing {
	int heurDistance(Node* start, Node* goal);

	std::vector<Node> aStar(Grid* grid, Node* start, Node* goal, Heuristic heur);
	std::vector<Node> dijkstra(Grid* grid, Node* start, Node* goal);
}

#endif