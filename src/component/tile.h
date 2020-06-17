#pragma once

#include <rect.h>
#include <texture.h>

#include <memory>

#include "wanderer_stdinc.h"

namespace wanderer {

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
