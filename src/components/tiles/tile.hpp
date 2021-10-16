#pragma once

#include <centurion.hpp>  // irect

#include "common/ints.hpp"
#include "common/texture_index.hpp"
#include "common/tile_id.hpp"
#include "core/game_constants.hpp"

namespace wanderer::comp {

/// \brief Represents a tile in a tileset.
/// \ingroup components
struct Tile final
{
  tile_id id{glob::empty_tile};  ///< Unique ID associated with the tile.
  texture_index texture{};       ///< Associated texture index.
  cen::irect src;                ///< Region in associated tileset.
  int32 depth{5};                ///< Rendering depth heuristic.
};

}  // namespace wanderer::comp
