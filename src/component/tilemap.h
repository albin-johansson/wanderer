#pragma once

#include <named_type.hpp>
#include <unordered_map>
#include <vector>

#include "map_position.h"
#include "tile_layer.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer::component {

using TilemapEntity = fluent::
    NamedType<entt::entity, struct TilemapEntityTag, fluent::Comparable>;

struct Tilemap final {
  TilesetEntity tileset{entt::entity{entt::null}};

  std::vector<TileLayerEntity> groundLayers;

  std::unordered_map<MapPosition, entt::entity> tileObjects; // FIXME

  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer::component
