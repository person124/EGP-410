#include "guiEditor.h"

#include "globalConst.h"

#include "gui/elements/guiAnimation.h"
#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiImage.h"

#include "gameMode/editor.h"

const int HEADER_TEXT = 0;
const int CURRENT_TILE = 1;
const int CURRENT_TILE_ANIM = 2;
const int CURRENT_SPAWN = 3;
const int CURRENT_SPAWN_ANIM = 4;
const int ARROW = 5;
const int SAVE_TEXT = 6;
const int LOAD_TEXT = 7;

GUIEditor::GUIEditor()
{
	setElementCount(8);
	mpElements[HEADER_TEXT] = new GUIFixedText(600, 0, "Edit Mode");

	mpElements[CURRENT_TILE] = new GUIFixedText(0, 5, "Current Tile:");
	mpElements[CURRENT_TILE_ANIM] = new GUIAnimation(160, 0, "tiles", 2);

	mpElements[CURRENT_SPAWN] = new GUIFixedText(0, 45, "Current Spawn:");
	mpElements[CURRENT_SPAWN_ANIM] = new GUIAnimation(170, 40, "editor_spawns", 2);

	mpElements[ARROW] = new GUIImage(0, 0, "editor_arrow", 2);

	mpElements[SAVE_TEXT] = new GUIFixedText(0, GC::WINDOW_HEIGHT, "Saved to editor.JO");
	mpElements[LOAD_TEXT] = new GUIFixedText(0, GC::WINDOW_HEIGHT, "Loaded from editor.JO");
}

void GUIEditor::changeSelected(int selected)
{
	int toMatch;
	if (selected == TILE)
		toMatch = CURRENT_TILE_ANIM;
	else if (selected == SPAWNS)
		toMatch = CURRENT_SPAWN_ANIM;

	int x = mpElements[toMatch]->getX() + 40;
	int y = mpElements[toMatch]->getY();

	mpElements[ARROW]->setX(x);
	mpElements[ARROW]->setY(y);
}

void GUIEditor::setTileFrame(int frame)
{
	((GUIAnimation*)mpElements[CURRENT_TILE_ANIM])->setFrame(frame);
}

void GUIEditor::setSpawnFrame(int frame)
{
	((GUIAnimation*)mpElements[CURRENT_SPAWN_ANIM])->setFrame(frame);
}

void GUIEditor::renderSaveMessage(bool val)
{
	mpElements[SAVE_TEXT]->setY(GC::WINDOW_HEIGHT - (val * GC::FONT_SIZE));
}

void GUIEditor::renderLoadMessage(bool val)
{
	mpElements[LOAD_TEXT]->setY(GC::WINDOW_HEIGHT - (val * GC::FONT_SIZE));
}