#pragma once

#include "entity_type.hpp"
#include "map_id.hpp"
#include "null_entity.hpp"
#include "tileset.hpp"

namespace wanderer::comp {
namespace detail {
struct tilemap_entity_t;
}

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
  using entity = entity_type<detail::tilemap_entity_t>;

  map_id id{0};  ///< The ID associated with the tilemap
  comp::tileset::entity tileset{null<comp::tileset>()};  ///< Associated tileset
  int humanoidLayer;  ///< The layer that humanoids inhabit
  float width;        ///< The width of the tilemap, in pixels
  float height;       ///< The height of the tilemap, in pixels
  int rows;           ///< The amount of rows in the tilemap
  int cols;           ///< The amount of columns in the tilemap
};

}  // namespace wanderer::comp
