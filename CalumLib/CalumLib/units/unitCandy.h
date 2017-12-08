#ifndef UNIT_CANDY_H
#define UNIT_CANDY_H

#include "units/unit.h"

class UnitCandy : public Unit
{
	public:
		UnitCandy(int x, int y, Unit* player);
		~UnitCandy();

		void update(double dt);
	private:
		Unit* mpPlayerRef;
};

#endif