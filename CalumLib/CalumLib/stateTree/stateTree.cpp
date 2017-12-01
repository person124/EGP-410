#include "stateTree.h"

#include "stateTree/state.h"

StateTree::StateTree()
{
}

StateTree::~StateTree()
{
	delete[] mpStates;
}

void StateTree::update(double dt)
{
	int newState = mpCurrentState->update(this, dt);
	if (newState != mpCurrentState->getID())
		transfer(newState);
}

int StateTree::getID()
{
	return mpCurrentState->getID();
}