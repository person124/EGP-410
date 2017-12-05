#ifndef STATE_TREE_H
#define STATE_TREE_H

#include "utils/trackable.h"

class State;
class Unit;

class StateTree : public Trackable
{
	public:
		StateTree(Unit* unit);
		virtual ~StateTree();

		void update(double dt);
		virtual void transfer(int state) {};

		int getID();

		Unit* getUnit() { return mpUnit; };
	protected:
		Unit* mpUnit;

		State* mpCurrentState;
		int mSize;
		State* mpStates;
};

#endif