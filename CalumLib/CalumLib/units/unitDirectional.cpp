#include "unitDirectional.h"

#include "graphics/animation.h"

#define _USE_MATH_DEFINES
#include <math.h>

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
}