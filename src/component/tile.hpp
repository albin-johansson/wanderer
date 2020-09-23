#pragma once

#include <rect.hpp>
#include <texture.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_entity_t;
}

/**
 * @struct tile
 *
 * @brief Represents a tile in a tileset.
 *
 * @details The `tile` struct represents a tile in a tileset. However, this
 * struct does not represent an actual tile object though, for efficiency
 * reasons.
 *
 * @headerfile tile.hpp
 */
struct tile final
{
  using entity = fluent::
      NamedType<entt::entity, detail::tile_entity_t, fluent::Comparable>;

  tile_id id{};                     /**< Unique ID associated with the tile. */
  cen::irect src;                   /**< Area of associated tilesheet that the
                                     * tile represents. */
  entt::handle<cen::texture> sheet; /**< Handle to the associated tilesheet. */
};

}  // namespace wanderer::comp
