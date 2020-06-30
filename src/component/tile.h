/**
 * @brief Provides the `Tile` component.
 * @file tile.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <rect.h>
#include <texture.h>

#include "wanderer_stdinc.h"

namespace wanderer::component {

/**
 * @brief Represents a tile in a tileset.
 * @details The `Tile` struct represents a tile in a tileset. However, this
 * struct does not represent an actual tile object though, for efficiency
 * reasons.
 * @struct Tile
 * @headerfile tile.h
 */
struct Tile final {
  using entity =
      fluent::NamedType<entt::entity, struct TileEntityTag, fluent::Comparable>;

  TileID id;                        /**< Unique ID associated with the tile. */
  ctn::IRect src;                   /**< Area of associated tilesheet that the
                                     * tile represents. */
  entt::handle<ctn::Texture> sheet; /**< Handle to the associated tilesheet. */
};

}  // namespace wanderer::component
