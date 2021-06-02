#pragma once

#include <unordered_map>  // unordered_map

#include "components/map/tile.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {

namespace tags {
struct tileset_tag;
}  // namespace tags

struct tileset final
{
  using entity = entity_type<tags::tileset_tag>;

  std::unordered_map<tile_id, comp::tile::entity> tiles;  // All available tiles entities.
};

void serialize(auto& archive, tileset& ts, uint32 version)
{
  archive(ts.tiles);
}

}  // namespace wanderer::comp
