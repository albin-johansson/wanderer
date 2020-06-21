#pragma once

#include <rect.h>
#include <texture.h>

#include <memory>
#include <named_type.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {

using TileEntity =
    fluent::NamedType<entt::entity, struct TileEntityTag, fluent::Comparable>;

/**
 * The Tile struct represents a tile in a tileset, not an actual tile object
 * though.
 */
struct Tile final {
  TileID id;
  centurion::IRect src;
  entt::handle<centurion::Texture> sheet;
};

}  // namespace wanderer
