#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdexcept>

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
  TTF_Init();

  int result = Catch::Session().run(argc, argv);

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
  return result;
}