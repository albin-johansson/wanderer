#pragma once

#include <vector>

#include "tileset.h"
#include "types.h"

namespace wanderer {

struct Tilemap final {
  entt::entity tileset;
  std::vector<entt::entity> groundLayers;
  std::vector<entt::entity> objectLayers;
  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer
