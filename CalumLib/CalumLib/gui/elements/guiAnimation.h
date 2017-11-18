#ifndef GUI_ANIMATION_H
#define GUI_ANIMATION_H

#include "gui/guiElement.h"

class Animation;

class GUIAnimation : public GUIElement
{
	public:
		GUIAnimation(int x, int y, Animation* anim, float scale = 1.0f);
		GUIAnimation(int x, int y, const char* animString, float scale = 1.0f);
		~GUIAnimation();

		void update(double dt);
		void draw();

		void setFrame(int frame);
	private:
		Animation* mpAni;
		float mScale;
};

#endif