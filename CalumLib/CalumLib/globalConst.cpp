#include "globalConst.h"

const int GC::WINDOW_WIDTH = 1280;
const int GC::WINDOW_HEIGHT = 720;


const int GC::FPS = 60;
const int GC::UPS = 60;


const float GC::MILLISECONDS = 1000.0f;
const float GC::tFPS = GC::MILLISECONDS / GC::FPS;
const float GC::UPStoFPS = (GC::FPS * GC::UPS) / GC::MILLISECONDS;

const int GC::TILE_SIZE = 32;
const int GC::TILE_HALF = GC::TILE_SIZE / 2;
const int GC::TILE_SCALE = 2;
const float GC::GRID_SCALE = 1.0f / GC::TILE_SIZE;

const int GC::FONT_SIZE = 20;

const char* GC::PATH_GRAPHICS_BUFFERS = "assets/graphics_buffers.dat";
const char* GC::PATH_ANIMATIONS = "assets/animations.dat";
const char* GC::PATH_AUDIO = "assets/audio_clips.dat";
const char* GC::PATH_FONT = "assets/cour.ttf";
const char* GC::PATH_EXTENSION = ".JO";
const char* GC::PATH_LEVELS = "maps";
const char* GC::PATH_EDITOR_SAVE = "maps/editor.JO";

const int GC::AUDIO_COUNT = 5;