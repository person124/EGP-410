#include "unitCoin.h"

UnitCoin::UnitCoin(int x, int y, Unit* player) : Unit("coin")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mpPlayerRef = player;
}

UnitCoin::~UnitCoin()
{
}

void UnitCoin::update(double dt)
{
	if (isUnitTouching(mpPlayerRef))
	{
		markForDeletion();
		//TODO add sound effect
	}
}