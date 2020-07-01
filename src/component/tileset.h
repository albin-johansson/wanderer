/**
 * @brief Provides the `Tileset` component.
 * @file tileset.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <unordered_map>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer::comp {

/**
 * @struct Tileset
 * @brief Represents a collection of tiles.
 *
 * @var Tileset::tiles
 * The tiles contained in the tileset. Maps tile identifiers with tile entity
 * identifiers.
 *
 * @headerfile tileset.h
 */
struct Tileset final {
  using entity = fluent::
      NamedType<entt::entity, struct TilesetEntityTag, fluent::Comparable>;

  std::unordered_map<TileID, Tile::entity> tiles;
};

}  // namespace wanderer::comp
