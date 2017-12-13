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
		void draw(float x, float y, GraphicsBuffer* buffer, float scale = 1.0f, float angle = 0);
		void draw(float x, float y, Sprite* sprite, float scale = 1.0f, float angle = 0);
		void draw(GraphicsBuffer* toDraw, float x, float y, GraphicsBuffer* buffer, float scale = 1.0f, float angle = 0);
        void draw(GraphicsBuffer* buffer, float x, float y, Sprite* sprite, float scale = 1.0f, float angle = 0);
        //Drawing buffers w/ offset
		void drawOffset(float x, float y, GraphicsBuffer* buffer, float scale = 1.0f, float angle = 0);
		void drawOffset(float x, float y, Sprite* sprite, float scale = 1.0f, float angle = 0);
		void drawOffset(GraphicsBuffer* toDraw, float x, float y, GraphicsBuffer* buffer, float scale = 1.0f, float angle = 0);
		void drawOffset(GraphicsBuffer* buffer, float x, float y, Sprite* sprite, float scale = 1.0f, float angle = 0);

		//Writing text
		void writeText(int x, int y, const Font& font, const Color& color, const std::string& text);
        void writeText(GraphicsBuffer* buffer, int x, int y, const Font& font, const Color& color, const std::string& text);
		//Writes text using the default font and color
		void writeText(int x, int y, const std::string& text);

		//Drawing Primitives
		void drawCircle(float x, float y, float radius, const Color& color);
		void drawLine(float x1, float y1, float x2, float y2, const Color& color);

		//Misc
		void clear();
		void flip();
		void setOffset(float x, float y);
		void offsetOffset(float xOff, float yOff);
	private:
		ALLEGRO_DISPLAY* mpDisplay;
		int mWidth, mHeight;

		float mXOffset, mYOffset;

		Color* mpColorBlack;

		Color* mpDefaultColor;
		Font* mpDefaultFont;
};

#endif