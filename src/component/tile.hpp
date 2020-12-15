#pragma once

#include <cen/rect.hpp>
#include <cen/texture.hpp>
#include <entt.hpp>

#include "depth.hpp"
#include "entity_type.hpp"
#include "texture_handle.hpp"
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
  texture_handle sheet;         ///< Handle to the associated tileset.
  cen::irect src;  ///< Region in associated tileset that the tile represents.
  depth_t depth{5};
};

}  // namespace wanderer::comp
