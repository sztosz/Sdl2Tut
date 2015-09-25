//
// Created by sztosz on 8/30/15.
//

#include "06.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

//The image we will load and show on the screen
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
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)){
        std::cout << "SDL_image could not be initilized! SDL_Error: " << IMG_GetError() << "\n";
      } else {
        gScreenSurface = SDL_GetWindowSurface(gWindow);
        success = true;
      }
    }
  }
  return success;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Image " << path.c_str() << " could not be loaded! IMG_Error: " << IMG_GetError() << "\n";
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      std::cout << "Image " << path.c_str() << " could not be optimized! SDL_Error: " << IMG_GetError() << "\n";
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMedia() {
  bool success = true;
  gCurrentSurface = loadSurface("06_extension_libraries_and_loading_other_image_formats/loaded.png");
  if (gCurrentSurface == NULL) {
    std::cout << "Image could not be loaded! SDL_Error: " << IMG_GetError() << "\n";
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gCurrentSurface);
  gCurrentSurface = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow == nullptr;
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
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      SDL_Rect stretchRect;
      stretchRect.x = 0;
      stretchRect.y = 0;
      stretchRect.w = SCREEN_WIDTH;
      stretchRect.h = SCREEN_HEIGHT;
      SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
      SDL_UpdateWindowSurface(gWindow);
    }
  }
  close();
  return 0;
}