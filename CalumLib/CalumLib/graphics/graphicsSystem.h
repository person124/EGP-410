#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "utils/trackable.h"

#include <string>

struct ALLEGRO_DISPLAY;

class GraphicsBuffer;
class Sprite;
class Color;
class Font;

class GraphicsSystem : public Trackable
{
	public:
		//De-Constructor
		GraphicsSystem(int width, int height);
		~GraphicsSystem();

		//Init/destroy
		bool init();
		void destroy();

		//Accessors
        void getBackBuffer(GraphicsBuffer* mBuffer);
		int getWidth();
		int getHeight();
		int getXOffset();
		int getYOffset();

		//drawing buffers
		void draw(int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
		void draw(int x, int y, Sprite* sprite, float scale = 1.0f);
		void draw(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
        void draw(GraphicsBuffer* buffer, int x, int y, Sprite* sprite, float scale = 1.0f);
        //Drawing buffers w/ offset
		void drawOffset(int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
		void drawOffset(int x, int y, Sprite* sprite, float scale = 1.0f);
		void drawOffset(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
		void drawOffset(GraphicsBuffer* buffer, int x, int y, Sprite* sprite, float scale = 1.0f);

		//Writing text
		void writeText(int x, int y, const Font& font, const Color& color, const std::string& text);
        void writeText(GraphicsBuffer* buffer, int x, int y, const Font& font, const Color& color, const std::string& text);
		//Writes text using the default font and color
		void writeText(int x, int y, const std::string& text);

		//Drawing Primitives
		void drawCircle(int x, int y, int radius, const Color& color);
		void drawLine(int x1, int y1, int x2, int y2, const Color& color);

		//Misc
		void clear();
		void flip();
		void setOffset(int x, int y);
		void offsetOffset(int xOff, int yOff);
	private:
		ALLEGRO_DISPLAY* mpDisplay;
		int mWidth, mHeight;

		int mXOffset, mYOffset;

		Color* mpColorBlack;

		Color* mpDefaultColor;
		Font* mpDefaultFont;
};

#endif