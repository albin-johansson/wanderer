#pragma once

#include <rect.h>

#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer {

struct Hitbox final {
  ctn::FRect bounds;
  std::vector<ctn::FRect> boxes;
};

}  // namespace wanderer