#pragma once

#include <key.h>

#include "wanderer_stdinc.h"

namespace wanderer {

struct Binds final {
  ctn::Key up{SDL_SCANCODE_W};
  ctn::Key right{SDL_SCANCODE_D};
  ctn::Key down{SDL_SCANCODE_S};
  ctn::Key left{SDL_SCANCODE_A};
  ctn::Key attack{SDL_SCANCODE_SPACE};
};

}  // namespace wanderer
