#pragma once

#include <centurion.hpp>  // irect

#include "common/depth.hpp"
#include "common/ints.hpp"
#include "common/texture_index.hpp"
#include "common/tile_id.hpp"
#include "core/game_constants.hpp"

namespace wanderer::comp {

/**
 * \struct tile
 *
 * \brief Represents a tile in a tileset.
 *
 * \details The `tile` struct represents a tile in a tileset. However, this
 * struct does not represent an actual tile object though, for efficiency
 * reasons.
 *
 * \headerfile tile.hpp
 */
struct tile final
{
  tile_id id{glob::empty_tile};  ///< Unique ID associated with the tile.
  texture_index texture{};       ///< Associated texture index.
  cen::irect src;                ///< Region in associated tileset.
  depth_t depth{5};              ///< Rendering depth heuristic.
};

}  // namespace wanderer::comp
