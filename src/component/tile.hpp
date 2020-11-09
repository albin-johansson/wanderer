#pragma once

#include <cen/rect.hpp>
#include <cen/texture.hpp>
#include <entt.hpp>

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
  tile_id id{};    ///< Unique ID associated with the tile.
  cen::irect src;  ///< Region in associated tileset that the tile represents.
  texture_handle sheet;  ///< Handle to the associated tileset.
};

}  // namespace wanderer::comp
