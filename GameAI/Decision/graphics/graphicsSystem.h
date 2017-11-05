#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "graphicsBuffer.h"
#include "font.h"
#include "color.h"
#include "sprite.h"

#include <string>

#include <Trackable.h>

struct ALLEGRO_DISPLAY;

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

		//drawing buffers
		void draw(int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
		void draw(int x, int y, Sprite& sprite, float scale = 1.0f);
		void draw(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
        void draw(GraphicsBuffer* buffer, int x, int y, Sprite& sprite, float scale = 1.0f);
        
		//Writing text
		void writeText(int x, int y, const Font& font, const Color& color, const std::string& text);
        void writeText(GraphicsBuffer* buffer, int x, int y, const Font& font, const Color& color, const std::string& text);
       
		//Misc
		void flip();
	private:
		ALLEGRO_DISPLAY* mpDisplay;
		int mWidth, mHeight;
};

void initError(std::string);

#endif