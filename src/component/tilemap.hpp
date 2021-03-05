#pragma once

#include <centurion.hpp>

#include "entity_type.hpp"
#include "ints.hpp"
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
  cen::farea size;    ///< The size of the tilemap, in pixels.
  int rows;           ///< The amount of rows in the tilemap
  int cols;           ///< The amount of columns in the tilemap
};

template <typename Archive>
void serialize(Archive& archive, tilemap& tm, u32 version)
{
  archive(tm.id, tm.tileset, tm.humanoidLayer, tm.size, tm.rows, tm.cols);
}

}  // namespace wanderer::comp
