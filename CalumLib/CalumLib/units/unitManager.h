#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "utils/trackable.h"

#include <vector>

class Unit;
class UnitPlayer;
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
		UnitPlayer* getPlayer() { return mpPlayer; };
	
		// Update Functions
		void update(double dt);
		void draw();
	
		// Special Unit Adders
		void addPlayer(int x, int y);
		void addSheerHeartAttack(int x, int y, int color);
		void addCoin(int x, int y);
	private:
		//This private function removes a unit completely
		void deleteLoop();
		void deleteUnit(unsigned int pos);
	
		std::vector<Unit*> mUnits;
		UnitPlayer* mpPlayer;
};

#endif