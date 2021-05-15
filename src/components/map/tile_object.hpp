#pragma once

#include "components/map/tile.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_object_t;
}  // namespace detail

struct tile_object final
{
  using entity = entity_type<detail::tile_object_t>;

  tile::entity tile_entity{null<tile>()};
};

void serialize(auto& archive, tile_object& to, u32 version)
{
  archive(to.tile_entity);
}

}  // namespace wanderer::comp
