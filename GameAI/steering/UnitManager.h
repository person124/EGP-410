#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>

#include "EventListener.h"

//For the typedef of SteeringFunc
#include "UnitSlottable.h"

class Unit;
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

		// Update Functions
		void update(float dt);
		void draw(GraphicsBuffer* buffer);

		// Event
		void handleEvent(const Event& theEvent);

		// Misc Functions
		Vector2 offsetPosition(Vector2& base, float distance);
		float randomBinomial();
	private:
		std::vector<Unit*> mUnits;

		SteeringFunc mFWander;

		float mMouseX, mMouseY;
};

#endif