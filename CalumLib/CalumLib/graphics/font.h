#ifndef FONT_H
#define FONT_H

#include "utils/trackable.h"

#include <string>

struct ALLEGRO_FONT;

class Font : public Trackable
{
	friend class GraphicsSystem;
	public:
		Font(int size, const std::string& path);
		~Font();

		int getSize();
		std::string getFilePath();
	private:
		ALLEGRO_FONT* mpFont;
		std::string mFilePath;
		int mSize;
};

#endif