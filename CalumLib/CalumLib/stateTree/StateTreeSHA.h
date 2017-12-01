#ifndef STATE_TREE_SHA_H
#define STATE_TREE_SHA_H

#include "stateTree/stateTree.h"

class Timer;

class StateTreeSHA : public StateTree
{
	public:
		StateTreeSHA();
		~StateTreeSHA();

		void transfer(int state);

		Timer* getTimer() { return mpTimer; };
	protected:
		Timer* mpTimer;
};

#endif