//
// Created by sztosz on 8/30/15.
//

#include "04.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface;

bool init() {
  bool success = false;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
  } else {
    gWindow = SDL_CreateWindow("SDL2_TUT",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
      success = true;
    }
  }
  return success;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Bitmap " << path.c_str() << " could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
  }
  return loadedSurface;
}

bool loadMedia() {
  bool success = true;
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
  if (gKeyPressSurfaces == NULL) {
    std::cout << "Bitmap could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
  if (gKeyPressSurfaces == NULL) {
    std::cout << "Bitmap could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
  if (gKeyPressSurfaces == NULL) {
    std::cout << "Bitmap could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
  if (gKeyPressSurfaces == NULL) {
    std::cout << "Bitmap could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_presses/right.bmp");
  if (gKeyPressSurfaces == NULL) {
    std::cout << "Bitmap could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  return success;
}

void close() {
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
  }
  gKeyPressSurfaces == NULL;
  SDL_DestroyWindow(gWindow);
  gWindow == NULL;
  SDL_Quit();
}

int main() {
  if (!init()) {
    std::cout << "Failed to initialize, exiting!!!" << "\n";
    return 1;
  }
  if (!loadMedia()) {
    std::cout << "Failed to load media, exiting!!!" << "\n";
    return 1;
  }
  bool quit = false;
  SDL_Event e;
  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
            break;
          case SDLK_DOWN:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
            break;
          case SDLK_RIGHT:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
            break;
          case SDLK_LEFT:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
            break;
          default:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            break;
        }
      }
      SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
    }
  }
  close();
  return 0;
}