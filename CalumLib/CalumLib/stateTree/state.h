#ifndef STATE_H
#define STATE_H

class StateTree;

typedef int(UpdateFunc)(StateTree* tree, double dt);

class State
{
	public:
		State();
		State(int id, UpdateFunc func);
		~State();

		int update(StateTree* tree, double dt);

		int getID() { return mID; };
	private:
		int mID;
		UpdateFunc* mUpdate;

};

#endif