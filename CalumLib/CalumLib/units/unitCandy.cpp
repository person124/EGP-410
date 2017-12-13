#include "unitCandy.h"

#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventCandyStart.h"

#include "graphics/animation.h"

#include "utils/timer.h"

UnitCandy::UnitCandy(int x, int y, Unit* player) : Unit("candy")
{
	mPos.x = (float)x;
	mPos.y = (float)y;

	mpPlayerRef = player;
	mAniScale = 2;
	mPauseAnim = false;

	mpTimer = new Timer;
	mEnabled = true;
}

UnitCandy::~UnitCandy()
{
	delete mpTimer;
}

void UnitCandy::update(const double& dt)
{
	if (mEnabled)
	{
		if (!mPauseAnim && !mpAnim->isFinished())
			mpAnim->update(dt);
		else
		{
			if (!mPauseAnim)
				mpTimer->start();

			mPauseAnim = true;
			mpAnim->setFrame(0);

			if (mpTimer->getElapsedTime() >= 2)
				mPauseAnim = false;
		}

		if (isUnitTouching(mpPlayerRef))
		{
			mEnabled = false;
			mpTimer->start();

			gpEventSystem->fireEvent(EventCandyStart());
		}
	}
	else
	{
		if (mpTimer->getElapsedTime() >= 60)
		{
			mpTimer->stop();
			mPauseAnim = false;
			mpAnim->setFrame(0);
			mEnabled = true;
		}
	}
}

void UnitCandy::draw()
{
	if (mEnabled)
		Unit::draw();
}