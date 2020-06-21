#pragma once

#include <named_type.hpp>
#include <vector>

#include "tile_layer.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer {

using TilemapEntity = fluent::
    NamedType<entt::entity, struct TilemapEntityTag, fluent::Comparable>;

struct Tilemap final {
  TilesetEntity tileset{entt::entity{entt::null}};
  std::vector<TileLayerEntity> groundLayers;
  std::vector<TileLayerEntity> objectLayers;
  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer
