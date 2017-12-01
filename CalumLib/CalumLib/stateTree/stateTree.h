#ifndef STATE_TREE_H
#define STATE_TREE_H

#include "utils/trackable.h"

class State;

class StateTree : public Trackable
{
	public:
		StateTree();
		virtual ~StateTree();

		void update(double dt);
		virtual void transfer(int state) {};

		int getID();
	protected:
		State* mpCurrentState;
		int mSize;
		State* mpStates;
};

#endif