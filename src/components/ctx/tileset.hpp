#pragma once

#include <unordered_map>  // unordered_map

#include "components/map/tile.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::ctx {
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
 * \headerfile tileset.hpp
 */
struct tileset final
{
  using entity = entity_type<detail::tileset_entity_t>;
  std::unordered_map<tile_id, comp::tile::entity> tiles;
};

void serialize(auto& archive, tileset& ts, u32 version)
{
  archive(ts.tiles);
}

}  // namespace wanderer::ctx
