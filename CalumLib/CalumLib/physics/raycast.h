#ifndef RAYCAST_H
#define RAYCAST_H

#include "physics/vector2.h"

class Grid;

bool RayCast(Grid* grid, const Vector2& begin, const Vector2& end);

#endif