#pragma once
#include <key.h>

namespace wanderer {

struct Binds final {
  centurion::Key up = SDL_SCANCODE_W;
  centurion::Key right = SDL_SCANCODE_D;
  centurion::Key down = SDL_SCANCODE_S;
  centurion::Key left = SDL_SCANCODE_A;
};

}  // namespace wanderer
