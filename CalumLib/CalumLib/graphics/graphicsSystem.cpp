#include "graphicsSystem.h"

#include "globalConst.h"

#include "graphics/graphicsBuffer.h"
#include "graphics/sprite.h"
#include "graphics/color.h"
#include "graphics/font.h"

#include "utils/ioUtils.h"

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

GraphicsSystem::GraphicsSystem(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mpDisplay = NULL;

	mXOffset = 0;
	mYOffset = 1;
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
		IOUtils::errorInitReport("Allegro");
		return false;
	}

	if (!al_init_image_addon())
	{
		IOUtils::errorInitReport("image addon");
		return false;
	}

	al_init_font_addon();

	if (!al_init_ttf_addon())
	{
		IOUtils::errorInitReport("ttf addon");
		return false;
	}

	if (!al_init_primitives_addon())
	{
		IOUtils::errorInitReport("primitives addon");
		return false;
	}

	mpDisplay = al_create_display(mWidth, mHeight);

	mpColorBlack = new Color(0, 0, 0);

	mpDefaultColor = new Color(255, 255, 255);
	mpDefaultFont = new Font(FONT_SIZE, PATH_FONT);

	return true;
}

void GraphicsSystem::destroy()
{
	delete mpColorBlack;

	delete mpDefaultColor;
	delete mpDefaultFont;

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

int GraphicsSystem::getXOffset()
{
	return mXOffset;
}

int GraphicsSystem::getYOffset()
{
	return mYOffset;
}

void GraphicsSystem::draw(int x, int y, GraphicsBuffer* buffer, float scale)
{
	al_draw_scaled_bitmap(buffer->mpBitmap, 0, 0, buffer->getWidth(), buffer->getHeight(),
		x, y, buffer->getWidth() * scale, buffer->getHeight() * scale, 0);
}

void GraphicsSystem::draw(int x, int y, Sprite* sprite, float scale)
{
	al_draw_scaled_bitmap(sprite->getBuffer()->mpBitmap, sprite->startX(), sprite->startY(), sprite->getWidth(),
		sprite->getHeight(), x, y, sprite->getWidth() * scale, sprite->getHeight() * scale, sprite->isFlipped());
}

void GraphicsSystem::draw(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale)
{
	al_set_target_bitmap(buffer->mpBitmap);

	draw(x, y, buffer, scale);

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::draw(GraphicsBuffer* buffer, int x, int y, Sprite* sprite, float scale)
{
	al_set_target_bitmap(buffer->mpBitmap);

	draw(x, y, sprite, scale);

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::drawOffset(int x, int y, GraphicsBuffer* buffer, float scale)
{
	draw(x - mXOffset, y - mYOffset, buffer, scale);
}

void GraphicsSystem::drawOffset(int x, int y, Sprite* sprite, float scale)
{
	draw(x - mXOffset, y - mYOffset, sprite, scale);
}

void GraphicsSystem::drawOffset(GraphicsBuffer* toDraw, int x, int y, GraphicsBuffer* buffer, float scale)
{
	draw(toDraw, x - mXOffset, y - mYOffset, buffer, scale);
}

void GraphicsSystem::drawOffset(GraphicsBuffer* buffer, int x, int y, Sprite* sprite, float scale)
{
	draw(buffer, x - mXOffset, y - mYOffset, sprite, scale);
}

void GraphicsSystem::writeText(int x, int y, const Font& font, const Color& color, const std::string& text)
{
    al_draw_text(font.mpFont, *color.mColor, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
}

void GraphicsSystem::writeText(GraphicsBuffer* buffer, int x, int y,
                               const Font& font, const Color& color, const std::string& text)
{
    al_set_target_bitmap(buffer->mpBitmap);

	writeText(x, y, font, color, text);

    al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::writeText(int x, int y, const std::string& text)
{
	writeText(x, y, *mpDefaultFont, *mpDefaultColor, text);
}

void GraphicsSystem::drawCircle(int x, int y, int radius, const Color& color)
{
	al_draw_filled_circle(x, y, radius, *color.mColor);
}

void GraphicsSystem::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
	al_draw_line(x1, y1, x2, y2, *color.mColor, 2);
}

void GraphicsSystem::clear()
{
	al_draw_filled_rectangle(0, 0, mWidth, mHeight, *mpColorBlack->mColor);
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::setOffset(int x, int y)
{
	mXOffset = x;
	mYOffset = y;
}

void GraphicsSystem::offsetOffset(int xOff, int yOff)
{
	mXOffset += xOff;
	mYOffset += yOff;
}