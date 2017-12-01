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
	int newState = mpCurrentState->update(dt);
	mpCurrentState = &mpStates[newState];
}

int StateTree::getID()
{
	return mpCurrentState->getID();
}