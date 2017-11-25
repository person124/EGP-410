#ifndef UNIT_DIRECTIONAL_H
#define UNIT_DIRECTIONAL_H

#include "units/unitPhys.h"

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIRECTION_COUNT
};

class UnitDirectional : public UnitPhys
{
	public:
		UnitDirectional();
		~UnitDirectional();

		void setAnim(Direction dir);
	protected:
		Animation** mpAnimFacing;
};

#endif