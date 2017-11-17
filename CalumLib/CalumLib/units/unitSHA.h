#ifndef UNIT_SHA_H
#define UNIT_SHA_H

#include "units/unit.h"

enum SHAColor
{
	blue,
	red,
	yellow,
	SHA_COLOR_COUNT
};

class UnitSHA : public Unit
{
	public:
		UnitSHA(SHAColor color);
		~UnitSHA();

		void update(double dt);
		void draw();
	private:
		Animation* mpAniBase;
		Animation* mpAniFear;
};

#endif