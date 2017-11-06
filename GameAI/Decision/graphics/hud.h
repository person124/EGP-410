#ifndef HUD_H
#define HUD_H

#include <Trackable.h>

class Font;
class Color;

class HUD : public Trackable
{
	public:
		HUD();
		~HUD();

		void update(int lives, int score, float fps);
		void drawFPS();
	private:
		Font* mpFont;
		Color* mpFontColor;
};

#endif