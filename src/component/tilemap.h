#pragma once

#include <named_type.hpp>
#include <vector>

#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer {

using Layer =
    fluent::NamedType<entt::entity, struct LayerTag, fluent::Comparable>;

struct Tilemap final {
  entt::entity tileset;
  std::vector<Layer> groundLayers;
  std::vector<Layer> objectLayers;
  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer
