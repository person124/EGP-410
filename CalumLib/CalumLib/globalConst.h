#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

struct GlobalConst
{
	const static int WINDOW_WIDTH;
	const static int WINDOW_HEIGHT;

	const static int FPS;
	const static int UPS;

	const static float MILLISECONDS;
	const static float tFPS;
	const static float UPStoFPS;

	const static int TILE_SIZE;
	const static int TILE_HALF;
	const static int TILE_SCALE;
	const static float GRID_SCALE;

	const static int FONT_SIZE;

	static const char* PATH_GRAPHICS_BUFFERS;
	static const char* PATH_ANIMATIONS;
	static const char* PATH_AUDIO;
	static const char* PATH_FONT;
	static const char* PATH_EXTENSION;
	static const char* PATH_LEVELS;
	static const char* PATH_EDITOR_SAVE;

	const static int AUDIO_COUNT;
};

typedef GlobalConst GC;

#endif