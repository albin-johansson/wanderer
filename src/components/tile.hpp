#pragma once

#include <centurion.hpp>  // irect

#include "core/game_constants.hpp"
#include "wanderer_std.hpp"

namespace wanderer::comp {

/// \brief Represents a tile in a tileset.
/// \ingroup components
struct Tile final
{
  TileID id{glob::empty_tile};  ///< Unique ID associated with the tile.
  usize texture{};              ///< Associated texture index.
  cen::irect src;               ///< Region in associated tileset.
  int32 depth{5};               ///< Rendering depth heuristic.
};

}  // namespace wanderer::comp
