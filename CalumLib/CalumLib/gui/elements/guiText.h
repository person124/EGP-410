#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include "gui/elements/guiFixedText.h"

#include <string>

class GUIText : public GUIFixedText
{
	public:
		GUIText(int x, int y, const std::string& text);
		GUIText(int x, int y);
		~GUIText();

		void updateText(const std::string& text);
		void updateText(const char* text);
		template <class T>
		void updateText(T number)
		{
			updateText(std::to_string(number));
		}
};

#endif