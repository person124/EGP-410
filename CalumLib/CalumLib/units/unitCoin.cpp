#include "unitCoin.h"

UnitCoin::UnitCoin(int x, int y) : Unit("coin")
{
	mPos.x = (float)x;
	mPos.y = (float)y;
}

UnitCoin::~UnitCoin()
{
}