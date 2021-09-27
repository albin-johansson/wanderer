#pragma once

#include <unordered_map>  // unordered_map

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "common/tile_id.hpp"
#include "components/tiles/tile.hpp"

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
