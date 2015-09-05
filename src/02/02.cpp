//
// Created by sztosz on 8/30/15.
//

#include "02.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

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

bool loadMedia() {
  bool success = true;
  gHelloWorld = SDL_LoadBMP("hello_world.bmp");
  if (gHelloWorld == NULL) {
    std::cout << "Bitmap hello_world.bmp could not be loaded! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld == NULL;
  SDL_DestroyWindow(gWindow);
  gWindow == NULL;
  SDL_Quit();
}

int main(){
  if (!init()){
    std::cout << "Failed to initialize, exiting!!!" << "\n";
    return 1;
  }
  if (!loadMedia()) {
    std::cout << "Failed to load media, exiting!!!" << "\n";
    return 1;
  }
  SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
  SDL_UpdateWindowSurface(gWindow);
  SDL_Delay(2000);
  close();
  return 0;
}