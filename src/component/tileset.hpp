#pragma once

#include <entt.hpp>
#include <named_type.hpp>
#include <unordered_map>  // unordered_map

#include "tile.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tileset_entity_t;
}

/**
 * @struct tileset
 *
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

  std::unordered_map<tile_id, tile::entity> tiles;
};

}  // namespace wanderer::comp
