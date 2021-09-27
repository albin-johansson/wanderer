#pragma once

#include <centurion.hpp>  // farea

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "common/map_id.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {

namespace tags {
struct tilemap_tag;
}  // namespace tags

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
  using entity = entity_type<tags::tilemap_tag>;

  map_id id{0};          ///< The ID associated with the tilemap
  int humanoid_layer{};  ///< The layer that humanoids inhabit
  cen::farea size;       ///< The size of the tilemap, in pixels.
  int row_count{};       ///< The amount of rows in the tilemap
  int col_count{};       ///< The amount of columns in the tilemap
};

void serialize(auto& archive, tilemap& tm, uint32 version)
{
  archive(tm.id, tm.humanoid_layer, tm.size, tm.row_count, tm.col_count);
}

}  // namespace wanderer::comp
