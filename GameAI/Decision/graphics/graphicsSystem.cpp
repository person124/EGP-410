#include "graphicsSystem.h"

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

GraphicsSystem::GraphicsSystem(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mpDisplay = NULL;
}

GraphicsSystem::~GraphicsSystem()
{
	if (mpDisplay != NULL)
		al_destroy_display(mpDisplay);
}

bool GraphicsSystem::init()
{
	if (!al_init())
	{
		initError("Allegro");
		return false;
	}

	if (!al_init_image_addon())
	{
		initError("image addon");
		return false;
	}

	al_init_font_addon();

	if (!al_init_ttf_addon())
	{
		initError("ttf addon");
		return false;
	}

	if (!al_init_primitives_addon())
	{
		initError("primitives addon");
		return false;
	}

	mpDisplay = al_create_display(mWidth, mHeight);
	return true;
}

void GraphicsSystem::destroy()
{
	al_destroy_display(mpDisplay);
	mpDisplay = NULL;
}

void GraphicsSystem::getBackBuffer(GraphicsBuffer* mBuffer)
{
    if (mBuffer != NULL)
        delete mBuffer;

    mBuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplay));
}

int GraphicsSystem::getWidth()
{
	return mWidth;
}

int GraphicsSystem::getHeight()
{
	return mHeight;
}

void GraphicsSystem::draw(int x, int y, GraphicsBuffer* buffer, float scale)
{
	al_draw_scaled_bitmap(buffer->mpBitmap, 0, 0, buffer->getWidth(), buffer->getHeight(),
		x, y, buffer->getWidth() * scale, buffer->getHeight() * scale, 0);
}

void GraphicsSystem::draw(int x, int y, Sprite& sprite, float scale)
{
	al_draw_scaled_bitmap(sprite.getBuffer()->mpBitmap, sprite.startX(), sprite.startY(), sprite.getWidth(),
		sprite.getHeight(), x, y, sprite.getWidth() * scale, sprite.getHeight() * scale, 0);
}

void GraphicsSystem::draw(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale)
{
	al_set_target_bitmap(buffer->mpBitmap);

	draw(x, y, buffer, scale);

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::draw(GraphicsBuffer* buffer, int x, int y, Sprite& sprite, float scale)
{
	al_set_target_bitmap(buffer->mpBitmap);

	draw(x, y, sprite, scale);

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::writeText(int x, int y, const Font& font, const Color& color, const std::string& text)
{
    al_draw_text(font.mpFont, color.mColor, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
}

void GraphicsSystem::writeText(GraphicsBuffer* buffer, int x, int y,
                               const Font& font, const Color& color, const std::string& text)
{
    al_set_target_bitmap(buffer->mpBitmap);

	writeText(x, y, font, color, text);

    al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::drawCircle(int x, int y, int radius, const Color& color)
{
	al_draw_filled_circle(x, y, radius, color.mColor);
}

void GraphicsSystem::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
	al_draw_line(x1, y1, x2, y2, color.mColor, 2);
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

//==========================================================================
//General Funtions

void initError(std::string str)
{
	std::cout << "ERROR: Failed to init " << str << "!\n";
}