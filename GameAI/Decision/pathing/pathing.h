#ifndef PATHING_H
#define PATHING_H

#include "pathing/pathList.h"

#include <vector>

class Grid;

namespace pathing {
	std::vector<Node> dijkstra(Grid* grid, Node* start, Node* goal);
}

#endif