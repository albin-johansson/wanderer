/**
 * @brief Provides the `Tile` component.
 * @file tile.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <rect.hpp>
#include <texture.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @brief Represents a tile in a tileset.
 * @details The `Tile` struct represents a tile in a tileset. However, this
 * struct does not represent an actual tile object though, for efficiency
 * reasons.
 * @struct Tile
 * @headerfile tile.hpp
 */
struct Tile final
{
  using entity =
      fluent::NamedType<entt::entity, struct TileEntityTag, fluent::Comparable>;

  tile_id id;                       /**< Unique ID associated with the tile. */
  cen::irect src;                   /**< Area of associated tilesheet that the
                                     * tile represents. */
  entt::handle<cen::texture> sheet; /**< Handle to the associated tilesheet. */
};

}  // namespace wanderer::comp
