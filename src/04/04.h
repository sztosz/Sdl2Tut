//
// Created by sztosz on 8/30/15.
//

#ifndef SDL2TUT_03_H
#define SDL2TUT_03_H


#include <SDL_surface.h>
//#include <bits/stringfwd.h>
//#include <bits/basic_string.h>
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//SDL_Surface *loadSurface(std::string path);
//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


#endif //SDL2TUT_02_H
