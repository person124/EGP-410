#include "guiGameOver.h"

#include "gui/elements/guiAnimation.h"

GUIGameOver::GUIGameOver()
{
	setElementCount(1);
	mpElements[0] = new GUIAnimation(0, 0, "kira_click_anim", 2.66666f);
}