#include "graphicsBuffer.h"

#include "graphics/color.h"

#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>

GraphicsBuffer::GraphicsBuffer(int width, int height, Color& color)
{
	mWidth = width;
	mHeight = height;
	mpBitmap = al_create_bitmap(width, height);
	mFilePath = "";

	al_set_target_bitmap(mpBitmap);
	al_draw_filled_rectangle(0, 0, width, height, *color.mColor);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

	useDestroy = true;
}

GraphicsBuffer::GraphicsBuffer(const std::string& path)
{
	mFilePath = path;

	mpBitmap = al_load_bitmap(path.c_str());
	mWidth = al_get_bitmap_width(mpBitmap);
	mHeight = al_get_bitmap_height(mpBitmap);

	al_convert_mask_to_alpha(mpBitmap, al_map_rgb(255, 0, 255));

	useDestroy = true;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* map)
{
	mFilePath = "";

	mpBitmap = map;
	mWidth = al_get_bitmap_width(mpBitmap);
	mHeight = al_get_bitmap_height(mpBitmap);

	useDestroy = false;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (useDestroy)
		al_destroy_bitmap(mpBitmap);
}

int GraphicsBuffer::getWidth()
{
	return mWidth;
}

int GraphicsBuffer::getHeight()
{
	return mHeight;
}

Color* GraphicsBuffer::getPixel(int x, int y)
{
	ALLEGRO_COLOR c = al_get_pixel(mpBitmap, x, y);
	return new Color(c.r, c.a, c.b);
}