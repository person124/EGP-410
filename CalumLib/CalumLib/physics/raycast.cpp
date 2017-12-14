#include "raycast.h"

#include "globalConst.h"

#include "pathing/grid.h"

//Uses this method
//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//Returns true if the cast succeeded
bool RayCast(Grid* grid, const Node& begin, const Node& end)
{
	int dX = end.x - begin.x;
	int dY = end.y - begin.y;

	//Check for horizontal or vertical lines
	if (begin.x == end.x) //Vertical Line
	{
		int x = begin.x;
		for (int y = begin.y; y != end.y; (dY > 0) ? y++ : y--)
		{
			if (grid->isSolid(x, y))
				return false;
		}

		return true;
	}
	else if (begin.y == end.y) //Horizontal line
	{
		int y = begin.y;
		for (int x = begin.x; x != end.x; (dX > 0) ? x++ : x--)
		{
			if (grid->isSolid(x, y))
				return false;
		}

		return true;
	}

	//Otherwise
	double dError = abs((double) dY / (double) dX);
	double error = 0;

	int y = begin.y;
	for (int x = begin.x; x != end.x; (dX > 0) ? x++ : x--)
	{
		if (grid->isSolid(x, y))
			return false;

		error += dError;
		while (error >= 0.5)
		{
			y += (int) copysign(1, dY);

			if (grid->isSolid(x, y))
				return false;

			error -= 1.0;
		}
	}

	return true;
}

bool RayCast(Grid* grid, const Vector2& begin, const Vector2& end)
{
	int tileStartX = (int)(begin.x * GC::GRID_SCALE);
	int tileStartY = (int)(begin.y * GC::GRID_SCALE);
	Node nodeStart = Node(tileStartX, tileStartY);

	int tileEndX = (int)(end.x * GC::GRID_SCALE);
	int tileEndY = (int)(end.y * GC::GRID_SCALE);
	Node nodeEnd = Node(tileEndX, tileEndY);

	return RayCast(grid, nodeStart, nodeEnd);
}