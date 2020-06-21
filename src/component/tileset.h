#pragma once

#include <named_type.hpp>
#include <unordered_map>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

using TilesetEntity = fluent::
    NamedType<entt::entity, struct TilesetEntityTag, fluent::Comparable>;

struct Tileset final {
  std::unordered_map<TileID, TileEntity> tiles;
};

}  // namespace wanderer
