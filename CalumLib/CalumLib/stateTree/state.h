#ifndef STATE_H
#define STATE_H

typedef int(UpdateFunc)(double dt);

class State
{
	public:
		State();
		State(int id, UpdateFunc func);
		~State();

		int update(double dt);

		int getID() { return mID; };
	private:
		int mID;
		UpdateFunc* mUpdate;

};

#endif