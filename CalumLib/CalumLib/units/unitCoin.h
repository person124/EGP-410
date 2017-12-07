#ifndef UNIT_COIN_H
#define UNIT_COIN_H

#include "units/unit.h"

class UnitCoin : public Unit
{
	public:
		UnitCoin(int x, int y, Unit* player);
		~UnitCoin();

		void update(double dt);
	private:
		Unit* mpPlayerRef;
};

#endif