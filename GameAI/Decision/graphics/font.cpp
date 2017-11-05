#include "font.h"

Font::Font(int size, const std::string& path)
{
	mSize = size;
	mFilePath = path;
	
	mpFont = al_load_ttf_font(mFilePath.c_str(), mSize, 0);
}

Font::~Font()
{
	al_destroy_font(mpFont);
}

int Font::getSize()
{
	return mSize;
}

std::string Font::getFilePath()
{
	return mFilePath;
}