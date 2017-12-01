#include "state.h"

State::State()
{
	mID = -1;
	mUpdate = 0;
}

State::State(const int id, UpdateFunc func)
{
	mID = id;
	mUpdate = func;
}

State::~State()
{
}

int State::update(double dt)
{
	return mUpdate(dt);
}