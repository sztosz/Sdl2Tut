//
// Created by sztosz on 8/30/15.
//

#ifndef SDL2TUT_06_H
#define SDL2TUT_06_H

#include <SDL_render.h>
#include <string>

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Load individual image as surface
SDL_Surface *loadSurface(std::string path);

#endif //SDL2TUT_06_H
