#pragma once

#include <unordered_map>

#include "types.h"

namespace wanderer {

struct Tileset final {
  std::unordered_map<TileID, entt::entity> tiles;
};

}  // namespace wanderer
