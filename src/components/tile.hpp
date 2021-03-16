#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "depth.hpp"
#include "entity_type.hpp"
#include "ints.hpp"
#include "texture_handle.hpp"
#include "texture_id.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_entity_t;
}

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
  using entity = entity_type<detail::tile_entity_t>;
  tile_id id{glob::emptyTile};  ///< Unique ID associated with the tile.
  texture_id texture;
  texture_handle sheet;  ///< Handle to the associated tileset.
  cen::irect src;  ///< Region in associated tileset that the tile represents.
  depth_t depth{5};
};

template <typename Archive>
void serialize(Archive& archive, tile& t, u32 version)
{
  archive(t.id, t.texture, t.src, t.depth);
}

}  // namespace wanderer::comp
