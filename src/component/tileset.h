#pragma once

#include <named_type.hpp>
#include <unordered_map>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct Tileset final {
  using entity = fluent::
      NamedType<entt::entity, struct TilesetEntityTag, fluent::Comparable>;

  std::unordered_map<TileID, TileEntity> tiles;
};

}  // namespace wanderer
