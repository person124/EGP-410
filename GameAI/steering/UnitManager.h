#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>

#include <Trackable.h>

class Unit;
class UnitPlayer;
class GraphicsBuffer;

class UnitManager : public Trackable
{
	public:
		UnitManager();
		~UnitManager();
		// Adding/Removing
		void addUnit(Unit*& unit);
		void removeUnit(unsigned int pos);
		void removeUnit(Unit*& unit);
		void removeAll();
		// Getters
		Unit*& getUnit(unsigned int pos);
		int getSize();
		// Update Functions
		void update(float dt);
		void draw(GraphicsBuffer* buffer);
	private:
		std::vector<Unit*> mUnits;

		UnitPlayer* mpPlayer;
};

#endif