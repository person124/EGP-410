#include "guiGameOverScore.h"

#include "globalConst.h"

#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiText.h"

GUIGameOverScore::GUIGameOverScore(int score)
{
	setElementCount(3);

	mpElements[0] = new GUIFixedText(0, 0, "Press Enter to Return to Menu...");

	mpElements[1] = new GUIFixedText(GC::WINDOW_WIDTH / 2, GC::WINDOW_HEIGHT / 2, "Score:");
	mpElements[2] = new GUIText(GC::WINDOW_WIDTH / 2 + 75, GC::WINDOW_HEIGHT / 2, "");
	
	((GUIText*)mpElements[2])->updateText(score);
}

GUIGameOverScore::~GUIGameOverScore()
{
}