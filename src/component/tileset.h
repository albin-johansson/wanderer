#pragma once

#include <unordered_map>

#include "wanderer_stdinc.h"

namespace wanderer {

struct Tileset final {
  std::unordered_map<TileID, entt::entity> tiles;
};

}  // namespace wanderer
