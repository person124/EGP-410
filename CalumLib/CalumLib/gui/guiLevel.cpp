#include "guiLevel.h"

#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiText.h"

enum ElementsType
{
	SCORE,
	SCORE_TEXT,
	ELEMENT_COUNT
};

GUILevel::GUILevel()
{
	setElementCount(ELEMENT_COUNT);

	mpElements[SCORE] = new GUIFixedText(0, 0, "Score:");
	mpElements[SCORE_TEXT] = new GUIText(75, 0, "0");
}

GUILevel::~GUILevel()
{
}

void GUILevel::setScore(int s)
{
	((GUIText*)mpElements[SCORE_TEXT])->updateText(s);
}