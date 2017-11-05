#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>

#include <Trackable.h>

class Unit;

class UnitManager : public Trackable
{
	public:
		UnitManager();
		~UnitManager();

		//Adding/removing
		void addUnit(Unit* unit);
		void removeUnit(Unit* unit);
		void removeUnit(unsigned int pos);
		void removeAll();

		//Getter
		Unit* getUnit(unsigned int pos);
		int getSize();

		//Update functions
		void update(float dt);
		void draw();
	private:
		std::vector<Unit*> mUnits;
};

#endif