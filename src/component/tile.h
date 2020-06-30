#pragma once

#include <rect.h>
#include <texture.h>

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * The Tile struct represents a tile in a tileset, not an actual tile object
 * though.
 */
struct Tile final {
  using entity =
      fluent::NamedType<entt::entity, struct TileEntityTag, fluent::Comparable>;

  TileID id;
  ctn::IRect src;
  entt::handle<ctn::Texture> sheet;
};

}  // namespace wanderer
