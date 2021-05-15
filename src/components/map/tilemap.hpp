#pragma once

#include <centurion.hpp>  // farea

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/map_id.hpp"
#include "core/ecs/null_entity.hpp"

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

  map_id id{0};          ///< The ID associated with the tilemap
  int humanoid_layer{};  ///< The layer that humanoids inhabit
  cen::farea size;       ///< The size of the tilemap, in pixels.
  int row_count{};       ///< The amount of rows in the tilemap
  int col_count{};       ///< The amount of columns in the tilemap
};

void serialize(auto& archive, tilemap& tm, u32 version)
{
  archive(tm.id, tm.humanoid_layer, tm.size, tm.row_count, tm.col_count);
}

}  // namespace wanderer::comp
