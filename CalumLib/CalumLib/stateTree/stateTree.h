#ifndef STATE_TREE_H
#define STATE_TREE_H

#include "utils/trackable.h"
/*
	States:
	Searching
	Fleeing
	Tracking
	Dead
*/

class StateTree : public Trackable
{
	public:
		StateTree();
		~StateTree();
};

#endif