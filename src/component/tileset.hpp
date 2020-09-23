/**
 * @brief Provides the `Tileset` component.
 * @file tileset.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <unordered_map>

#include "tile.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Tileset
 * @brief Represents a collection of tiles.
 *
 * @var Tileset::tiles
 * The tiles contained in the tileset. Maps tile identifiers with tile entity
 * identifiers.
 *
 * @headerfile tileset.hpp
 */
struct Tileset final {
  using entity = fluent::
      NamedType<entt::entity, struct TilesetEntityTag, fluent::Comparable>;

  std::unordered_map<tile_id, Tile::entity> tiles;
};

}  // namespace wanderer::comp
