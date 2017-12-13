#ifndef RAYCAST_H
#define RAYCAST_H

#include "pathing/node.h"

#include "physics/vector2.h"

class Grid;

bool RayCast(Grid* grid, const Node& begin, const Node& end);
bool RayCast(Grid* grid, const Vector2& begin, const Vector2& end);

#endif