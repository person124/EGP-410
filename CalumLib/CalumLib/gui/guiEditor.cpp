#include "guiEditor.h"

#include "editor/editor.h"

#include "gui/elements/guiAnimation.h"
#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiImage.h"

const int HEADER_TEXT = 0;
const int CURRENT_TILE = 1;
const int CURRENT_TILE_ANIM = 2;
const int CURRENT_SPAWN = 3;
const int CURRENT_SPAWN_ANIM = 4;
const int ARROW = 5;

GUIEditor::GUIEditor()
{
	setElementCount(6);
	mpElements[HEADER_TEXT] = new GUIFixedText(600, 0, "Edit Mode");

	mpElements[CURRENT_TILE] = new GUIFixedText(0, 5, "Current Tile:");
	mpElements[CURRENT_TILE_ANIM] = new GUIAnimation(160, 0, "tiles", 2);

	mpElements[CURRENT_SPAWN] = new GUIFixedText(0, 45, "Current Spawn:");
	mpElements[CURRENT_SPAWN_ANIM] = new GUIAnimation(170, 40, "editor_spawns", 2);

	mpElements[ARROW] = new GUIImage(0, 0, "editor_arrow", 2);
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