//
// Created by sztosz on 10/12/15.
//

#include "07.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

//The window renderer
SDL_Renderer *gRenderer = nullptr;

//Current displayed texture
SDL_Texture *gTexture = nullptr;

//The image we will load and show on the screen
SDL_Surface *gCurrentSurface = nullptr;

bool init() {
  bool success = false;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
  }
  else {
    gWindow = SDL_CreateWindow("SDL2_TUT",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    }
    else {
      //create renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        std::cout << "Rendered could not be initialized! SDL_Error: " << SDL_GetError() << "\n";
      }
      else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          std::cout << "SDL_image could not be initilized! SDL_Error: " << IMG_GetError() << "\n";
        }
        else {
          gScreenSurface = SDL_GetWindowSurface(gWindow);
          success = true;
        }
      }
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  gTexture = loadTexture("07_texture_loading_and_rendering/texture.png");
  if (gTexture == NULL) {
    std::cout << "Texture could not be loaded!\n";
    success = false;
  }
  return success;
}

void close() {
  SDL_DestroyTexture(gTexture);
  gTexture = nullptr;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow == nullptr;
  IMG_Quit();
  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Image " << path.c_str() << " could not be loaded! IMG_Error: " << IMG_GetError() << "\n";
  }
  else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      std::cout << "Image " << path.c_str() << " could not be optimized! SDL_Error: " << IMG_GetError() << "\n";
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

SDL_Texture *loadTexture(std::string path) {
  SDL_Texture *newTexture = nullptr;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Image " << path.c_str() << " could not be loaded! IMG_Error: " << IMG_GetError() << "\n";
  }
  else {
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL){
      std::cout << "Texture " << path.c_str() << " could not be created! SDL_Error: " << SDL_GetError() << "\n";
    }
    loadedSurface = nullptr;
  }
  return newTexture;
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
      SDL_RenderClear(gRenderer);
      SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
      SDL_RenderPresent(gRenderer);
    }
  }
  close();
  return 0;
}
