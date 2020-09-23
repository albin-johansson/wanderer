#pragma once

#include <unordered_map>

#include "tile.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::comp {
namespace detail {
struct tileset_entity_t;
}

/**
 * @struct tileset
 * @brief Represents a collection of tiles.
 *
 * @var tileset::tiles
 * The tiles contained in the tileset. Maps tile identifiers with tile entity
 * identifiers.
 *
 * @headerfile tileset.hpp
 */
struct tileset final
{
  using entity = fluent::
      NamedType<entt::entity, detail::tileset_entity_t, fluent::Comparable>;

  std::unordered_map<tile_id, Tile::entity> tiles;
};

}  // namespace wanderer::comp
