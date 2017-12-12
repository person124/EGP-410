#ifndef GUI_GAME_OVER_SCORE_H
#define GUI_GAME_OVER_SCORE_H

#include "gui/gui.h"

class GUIGameOverScore : public GUI
{
	public:
		GUIGameOverScore(int score);
		~GUIGameOverScore();
};

#endif