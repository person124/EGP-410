#ifndef STATE_TREE_SHA_H
#define STATE_TREE_SHA_H

#include "stateTree/stateTree.h"

class Timer;

class UnitPlayer;

class StateTreeSHA : public StateTree
{
	public:
		StateTreeSHA(Unit* unit);
		~StateTreeSHA();

		void transfer(int state);

		Timer* getTimer() { return mpTimer; };

		UnitPlayer* getPlayer();
	private:
		Timer* mpTimer;

};

#endif