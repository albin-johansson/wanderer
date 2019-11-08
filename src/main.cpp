#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "wanderer_core.h"
#include "wanderer_core_factory.h"
#include "wanderer_controller.h"
#include "wanderer_controller_factory.h"

static void Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to initialize SDL!" << std::endl;
  }
  IMG_Init(IMG_INIT_PNG);
}

static void Run() {
  using namespace wanderer::core;
  using namespace wanderer::controller;
  using namespace wanderer::view;

  IWandererCore_uptr core = CreateCore();
  IWandererController_uptr controller = CreateController(std::move(core));

  controller->Run();
}

static void Quit() {
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char** argv) {
  Init();
  Run();
  Quit();
  return 0;
}