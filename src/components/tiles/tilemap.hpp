#pragma once

#include <centurion.hpp>  // farea

#include "common/ints.hpp"
#include "common/map_id.hpp"

namespace wanderer::comp {

/**
 * \struct tilemap
 *
 * \brief Represents a tilemap.
 *
 * \note An important assumption in the game is that every level has *one*
 * associated tilemap, and each level features its own registry.
 *
 * \see level
 *
 * \headerfile tilemap.hpp
 */
struct tilemap final
{
  map_id id{0};            ///< The ID associated with the tilemap
  int32 humanoid_layer{};  ///< The layer that humanoids inhabit
  cen::farea size;         ///< The size of the tilemap, in pixels.
  uint64 row_count{};      ///< The amount of rows in the tilemap
  uint64 col_count{};      ///< The amount of columns in the tilemap
};

}  // namespace wanderer::comp
