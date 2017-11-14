#ifndef GRAPHICS_BUFFER_H
#define GRAPHICS_BUFFER_H

#include "graphics/color.h"

#include "utils/trackable.h"

#include <string>

struct ALLEGRO_BITMAP;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
	public:
		GraphicsBuffer(const std::string& path);
		GraphicsBuffer(int width, int height, Color& color);
		~GraphicsBuffer();
		int getWidth();
		int getHeight();
	private:
		GraphicsBuffer(ALLEGRO_BITMAP* map);
		ALLEGRO_BITMAP* mpBitmap;
		int mWidth, mHeight;
		std::string mFilePath;
		bool useDestroy;
};

#endif