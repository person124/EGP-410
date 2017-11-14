#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FPS 60 //Modify this to change fps
#define UPS 60 //Modify this to change ups

#define MILLISECONDS 1000.0
#define tFPS (MILLISECONDS / FPS)
#define UPStoFPS ((FPS * UPS) / MILLISECONDS)

#define TILE_SIZE 32
#define TILE_HALF (TILE_SIZE / 2)
#define TILE_SCALE 2

#define FONT_SIZE 20

#define PATH_GRAPHICS_BUFFERS "assets/graphics_buffers.dat"
#define PATH_ANIMATIONS "assets/animations.dat"
#define PATH_AUDIO "assets/audio_clips.dat"
#define PATH_FONT "assets/cour.ttf"
#define PATH_GRID_SAVE "assets/grid_info.dat"

#define AUDIO_SAMPLES 5

#endif