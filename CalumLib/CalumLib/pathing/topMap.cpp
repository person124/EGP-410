#include "topMap.h"

#include "globalConst.h"

#include "pathing/grid.h"

int min(int var1, int var2)
{
	if (var1 <= var2)
		return var1;
	return var2;
}

TopMap::TopMap(Grid* grid)
{
	mpGridReference = grid;

	mWidth = grid->getWidth() / GC::TOP_MAP_RESOLUTION;
	mHeight = grid->getHeight() / GC::TOP_MAP_RESOLUTION;

	if (grid->getWidth() % GC::TOP_MAP_RESOLUTION != 0)
		mWidth++;
	if (grid->getHeight() % GC::TOP_MAP_RESOLUTION != 0)
		mHeight++;

	mpNodes = NULL;
}

TopMap::~TopMap()
{
	if (mpNodes != NULL)
		delete[] mpNodes;
}

void TopMap::generateNodes()
{
	mpNodes = new TopNode[mWidth * mHeight];

	for (int yp = 0; yp < mHeight; yp++)
		for (int xp = 0; xp < mWidth; xp++)
		{
			int pos = xp + yp * mWidth;
			TopNode node = TopNode(xp, yp);

			int x = xp * 5;
			int y = yp * 5;

			int xDist = min(GC::TOP_MAP_RESOLUTION, mpGridReference->getWidth() - x);
			int yDist = min(GC::TOP_MAP_RESOLUTION, mpGridReference->getHeight() - y);
			
			if (yp == 0)
				node.up = false;
			if (xp == 0)
				node.left = false;

			//Test Up
			if (yp == 0)
				node.up = false;
			else
			{
				for (int i = 0; i < xDist; i++)
				{
					//Check node and node above to see if both non solid
					if (mpGridReference->isSolid(x + i, y) &&
						mpGridReference->isSolid(x + i, y - 1))
					{
						node.up = true;
						break;
					}
				}
			}

			//Test Down
			if (yp == mHeight - 1)
				node.down = false;
			else
			{
				int yVal = y + GC::TOP_MAP_RESOLUTION;

				for (int i = 0; i < xDist; i++)
				{
					if (mpGridReference->isSolid(x + i, yVal) &&
						mpGridReference->isSolid(x + y, yVal + 1))
					{
						node.down = true;
						break;
					}
				}
			}
			
			//Test Left
			if (xp == 0)
				node.left = false;
			else
			{
				for (int i = 0; i < yDist; i++)
				{
					if (mpGridReference->isSolid(x, y + i) &&
						mpGridReference->isSolid(x - 1, y + i))
					{
						node.left = true;
						break;
					}
				}
			}

			//Test Right
			if (xp == mWidth - 1)
				node.right = false;
			else
			{
				int xVal = x + GC::TOP_MAP_RESOLUTION;

				for (int i = 0; i < yDist; i++)
				{
					if (mpGridReference->isSolid(xVal, y + i) &&
						mpGridReference->isSolid(xVal + 1, y + i))
					{
						node.right = true;
						break;
					}
				}
			}

			mpNodes[pos] = node;
		}
}