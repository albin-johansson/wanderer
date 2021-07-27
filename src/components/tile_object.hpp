#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"
#include "core/ecs/null_entity.hpp"
#include "tile.hpp"

namespace wanderer::comp {

namespace tags {
struct tile_object_tag;
}  // namespace tags

struct tile_object final
{
  using entity = entity_type<tags::tile_object_tag>;

  tile::entity tile_entity{null<tile>()};
};

void serialize(auto& archive, tile_object& to, uint32 version)
{
  archive(to.tile_entity);
}

}  // namespace wanderer::comp
