#include "mainMenu.h"

#include "gui/guiMainMenu.h"

MainMenu::MainMenu()
{
	mpGUI = new GUIMainMenu();
}

void MainMenu::draw()
{
	mpGUI->draw();
}