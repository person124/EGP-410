#ifndef STATE_TREE_H
#define STATE_TREE_H

#include "utils/trackable.h"

class State;

class StateTree : public Trackable
{
	public:
		StateTree();
		~StateTree();

		void update(double dt);

		int getID();
	protected:
		State* mpCurrentState;
		int mSize;
		State* mpStates;
};

#endif