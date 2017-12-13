#include "unitCoin.h"

#include "events/eventSystem.h"
#include "events/eventPickupCoin.h"

UnitCoin::UnitCoin(int x, int y, Unit* player) : Unit("coin")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mpPlayerRef = player;
}

UnitCoin::~UnitCoin()
{
}

void UnitCoin::update(const double& dt)
{
	if (isUnitTouching(mpPlayerRef))
	{
		markForDeletion();
		gpEventSystem->fireEvent(EventPickupCoin());
		//TODO add sound effect
	}
}