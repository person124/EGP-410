#ifndef UNIT_SHA_H
#define UNIT_SHA_H

#include "units/unitPhys.h"

enum SHAColor
{
	blue,
	red,
	yellow,
	SHA_COLOR_COUNT
};

class StateTreeSHA;

class UnitSHA : public UnitPhys
{
	public:
		UnitSHA(SHAColor color);
		~UnitSHA();

		void update(double dt);
		void draw();

		int getCurrentState();
	private:
		Animation* mpAniBase;
		Animation* mpAniFear;
		Animation* mpAniEnraged;
		Animation* mpAniRespawn;

		StateTreeSHA* mpStateTree;
};

#endif