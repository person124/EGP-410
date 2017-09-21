#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>

#include "EventListener.h"
//#include "Phys.h"

class Unit;
class UnitPlayer;
class GraphicsBuffer;
struct Vector2;

class UnitManager : public EventListener
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
		UnitPlayer* getPlayer() { return mpPlayer; };

		// Update Functions
		void update(float dt);
		void draw(GraphicsBuffer* buffer);

		// Event
		void handleEvent(const Event& theEvent);

		// Misc Functions
		Vector2 getRandDistFromPlayer(float distance);
	private:
		std::vector<Unit*> mUnits;
		UnitPlayer* mpPlayer;
};

#endif