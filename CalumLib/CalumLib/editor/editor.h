#ifndef EDITOR_H
#define EDITOR_H

#include "events/eventListener.h"

class Grid;

enum EditorSelections
{
	TILE,
	SPAWNS,
	EDITOR_SELECTIONS_COUNT
};

class Editor : public EventListener
{
	public:
		Editor();
		~Editor();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		Grid* mpGrid;
		EditorSelections mCurrentType;
		int mCurrent[EDITOR_SELECTIONS_COUNT];
		int mMax[EDITOR_SELECTIONS_COUNT];
};

EditorSelections operator++(EditorSelections& sel, int);
EditorSelections operator--(EditorSelections& sel, int);

#endif