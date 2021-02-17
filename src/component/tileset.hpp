#pragma once

#include <entt.hpp>
#include <unordered_map>  // unordered_map

#include "entity_type.hpp"
#include "ints.hpp"
#include "tile.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tileset_entity_t;
}

/**
 * \struct tileset
 *
 * \brief Represents a collection of tiles.
 *
 * \var tileset::tiles
 * The tiles contained in the tileset. Maps tile identifiers with tile entity
 * identifiers.
 *
 * \todo is this a component? Or should it be a member of the game class.
 *
 * \headerfile tileset.hpp
 */
struct tileset final
{
  using entity = entity_type<detail::tileset_entity_t>;
  std::unordered_map<tile_id, tile::entity> tiles;
};

template <typename Archive>
void serialize(Archive& archive, tileset& ts, u32 version)
{
  archive(ts.tiles);
}

}  // namespace wanderer::comp
