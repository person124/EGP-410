#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <allegro5\allegro5.h>

#include <string>

class InputManager
{
	public:
		InputManager();
		~InputManager();
		bool init();
		void update();
		void draw();
	private:
		ALLEGRO_KEYBOARD_STATE mKeyState;
		ALLEGRO_MOUSE_STATE mMouseState;
		std::string mStrMousePos;
};

#endif