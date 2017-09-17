// MadeByCalum
#ifndef UNIT_DYNAMIC_H
#define UNIT_DYNAMIC_H

#include "Unit.h"

class UnitDynamic : public Unit
{
	public:
		UnitDynamic(Sprite* sprite, bool isArrive);
		~UnitDynamic();
		void update(float dt);

		//Movement functions
		void seek(Vector2& target);
		void arrive(Vector2& target);
	private:
		bool mArrive;
};

#endif