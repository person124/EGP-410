#include "raycast.h"

#include "globalConst.h"

#include "pathing/grid.h"

//Uses this method
//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//TODO FIX!
bool RayCast(Grid* grid, const Vector2& begin, const Vector2& end)
{
	int tileStartX = (int)(begin.x / TILE_SIZE);
	int tileStartY = (int)(begin.y / TILE_SIZE);

	int tileEndX = (int)(end.x / TILE_SIZE);
	int tileEndY = (int)(end.y / TILE_SIZE);

	int dX = tileEndX - tileStartX;
	int dY = tileEndY - tileStartY;

	//Check for horizontal or vertical lines
	if (tileStartX == tileEndX) //Vertical Line
	{
		int x = tileStartX;
		for (int y = tileStartX; y != tileEndX; (dY > 0) ? y++ : y--)
		{
			if (grid->isSolid(x, y))
				return false;
		}
	}
	else if (tileStartY == tileEndY) //Horizontal line
	{
		int y = tileStartY;
		for (int x = tileStartX; x != tileEndX; (dX > 0) ? x++ : x--)
		{
			if (grid->isSolid(x, y))
				return false;
		}
	}

	//Otherwise
	double dError = abs((double) dY / (double) dX);
	double error = 0;

	int y = tileStartY;
	for (int x = tileStartX; x != tileEndX; (dX > 0) ? x++ : x--)
	{
		if (grid->isSolid(x, y))
			return false;

		error += dError;
		while (error >= 0.5)
		{
			y += (int) copysign(1, dY);
			error -= 1.0;
		}
	}

	return true;
}