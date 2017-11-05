#ifndef HUD_H
#define HUD_H

#include <Trackable.h>

class Font;
class Color;

class Hud : public Trackable
{
	public:
		Hud();
		~Hud();

		void update(int lives, int score, float fps);
		void drawFPS();
	private:
		Font* mpFont;
		Color* mpFontColor;
};

#endif