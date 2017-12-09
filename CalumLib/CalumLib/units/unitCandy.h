#ifndef UNIT_CANDY_H
#define UNIT_CANDY_H

#include "units/unit.h"

class Timer;

class UnitCandy : public Unit
{
	public:
		UnitCandy(int x, int y, Unit* player);
		~UnitCandy();

		void update(double dt);
		void draw();
	private:
		Unit* mpPlayerRef;
		bool mPauseAnim;

		Timer* mpTimer;
		bool mEnabled;
};

#endif