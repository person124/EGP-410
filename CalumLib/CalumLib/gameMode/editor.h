#ifndef EDITOR_H
#define EDITOR_H

#include "events/eventListener.h"

#include "gameMode/gameMode.h"

class Grid;
class GUIEditor;
class GraphicsSystem;
class Timer;

enum EditorSelections
{
	TILE,
	SPAWNS,
	EDITOR_SELECTIONS_COUNT
};

//TODO
//Add ability to change size, add ability to specifiy nav zones

class Editor : public GameMode, public EventListener
{
	public:
		Editor();
		~Editor();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		GUIEditor* mpGEdit;
		GraphicsSystem* mpGraphics;

		bool mDrawSolid;

		EditorSelections mCurrentType;
		int mCurrent[EDITOR_SELECTIONS_COUNT];
		int mMax[EDITOR_SELECTIONS_COUNT];

		Timer* mpTimer;
};

EditorSelections operator++(EditorSelections& sel, int);
EditorSelections operator--(EditorSelections& sel, int);

#endif