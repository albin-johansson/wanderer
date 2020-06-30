#pragma once

#include <named_type.hpp>
#include <unordered_map>
#include <vector>

#include "map_position.h"
#include "tile_layer.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer::component {

struct Tilemap final {
  using entity = fluent::
      NamedType<entt::entity, struct TilemapEntityTag, fluent::Comparable>;

  Tileset::entity tileset = null_entity<Tileset>();

  std::vector<TileLayer::entity> groundLayers;

  std::unordered_map<MapPosition, entt::entity> tileObjects;  // FIXME

  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer::component
