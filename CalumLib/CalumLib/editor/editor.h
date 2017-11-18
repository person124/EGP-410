#ifndef EDITOR_H
#define EDITOR_H

#include "events/eventListener.h"

class Grid;
class GUIEditor;
class GraphicsSystem;

enum EditorSelections
{
	TILE,
	SPAWNS,
	EDITOR_SELECTIONS_COUNT
};

class Editor : public EventListener
{
	public:
		Editor(GUIEditor* gui);
		~Editor();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		GUIEditor* mpGUI;
		GraphicsSystem* mpGraphics;

		bool mDrawSolid;

		Grid* mpGrid;
		EditorSelections mCurrentType;
		int mCurrent[EDITOR_SELECTIONS_COUNT];
		int mMax[EDITOR_SELECTIONS_COUNT];
};

EditorSelections operator++(EditorSelections& sel, int);
EditorSelections operator--(EditorSelections& sel, int);

#endif