#pragma once

#include "entity_type.hpp"
#include "ints.hpp"
#include "null_entity.hpp"
#include "tile.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_object_t;
}  // namespace detail

struct tile_object final
{
  using entity = entity_type<detail::tile_object_t>;
  tile::entity tileEntity{null<tile>()};
};

void serialize(auto& archive, tile_object& to, u32 version)
{
  archive(to.tileEntity);
}

}  // namespace wanderer::comp
