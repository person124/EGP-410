#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "utils/trackable.h"

#include <vector>

class Unit;
struct Vector2;

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	// Adding/Removing
	void addUnit(Unit* unit);
	void removeUnit(unsigned int pos);
	void removeUnit(Unit* unit);
	void removeAll();

	// Getters
	Unit* getUnit(unsigned int pos);
	Unit* getUnitAtPos(Vector2* pos);
	int getSize();

	// Update Functions
	void update(double dt);
	void draw();
private:
	std::vector<Unit*> mUnits;
};

#endif