#include "unitDirectional.h"

#include "graphics/animation.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float PI_4 = (float)M_PI_4;
const float PI_3_4 = 3 * PI_4;
const float PI_5_4 = 5 * PI_4;
const float PI_7_4 = 5 * PI_4;

UnitDirectional::UnitDirectional() : UnitPhys("")
{
	mpAnimFacing = new Animation*[DIRECTION_COUNT];
}

UnitDirectional::~UnitDirectional()
{
	mpAnim = NULL;

	for (int i = 0; i < DIRECTION_COUNT; i++)
		delete mpAnimFacing[i];
	delete[] mpAnimFacing;
}

void UnitDirectional::setAnim(Direction dir)
{
	mpAnim = mpAnimFacing[(int)dir];
}

void UnitDirectional::setAnimFromAngle()
{
	if (mAngle < PI_4)
		setAnim(RIGHT);
	else if (mAngle < PI_3_4)
		setAnim(UP);
	else if (mAngle < PI_5_4)
		setAngle(RIGHT);
	else if (mAngle < PI_7_4)
		setAngle(DOWN);
	else
		setAngle(RIGHT);
}