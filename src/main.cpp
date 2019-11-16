#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include "wanderer_controller.h"
#include "wanderer_controller_factory.h"

static void Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to initialize SDL! Error: " << SDL_GetError() << "\n";
  }
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    std::cerr << "Failed to initialize SDL_image! Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() == -1) {
    std::cerr << "Failed to initialize SDL_ttf! Error: " << SDL_GetError() << "\n";
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC) == 0) {
    std::cerr << "Failed to initialize SDL_mixer! Error: " << SDL_GetError() << "\n";
  }
}

static void Run() {
  using namespace wanderer::controller;

  IWandererController_uptr controller = CreateController();
  controller->Run();
}

static void Quit() {
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}

int main(int argc, char** argv) {
  Init();
  Run();
  Quit();
  return 0;
}