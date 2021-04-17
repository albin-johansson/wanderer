#pragma once

#include <centurion.hpp>  // farea

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/map_id.hpp"
#include "core/null_entity.hpp"
#include "ctx/tileset.hpp"

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

  map_id id{0};       ///< The ID associated with the tilemap
  int humanoidLayer;  ///< The layer that humanoids inhabit
  cen::farea size;    ///< The size of the tilemap, in pixels.
  int rows;           ///< The amount of rows in the tilemap
  int cols;           ///< The amount of columns in the tilemap
};

void serialize(auto& archive, tilemap& tm, u32 version)
{
  archive(tm.id, tm.humanoidLayer, tm.size, tm.rows, tm.cols);
}

}  // namespace wanderer::comp
