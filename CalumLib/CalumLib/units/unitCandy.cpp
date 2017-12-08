#include "unitCandy.h"

#include "events/eventSystem.h"
#include "events/eventCandyStart.h"

UnitCandy::UnitCandy(int x, int y, Unit* player) : Unit("candy")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mpPlayerRef = player;
	mAniScale = 2;
}

UnitCandy::~UnitCandy()
{
}

void UnitCandy::update(double dt)
{
	if (isUnitTouching(mpPlayerRef))
	{
		//TODO just disable for a bit
		markForDeletion();

		gpEventSystem->fireEvent(EventCandyStart());
	}
}