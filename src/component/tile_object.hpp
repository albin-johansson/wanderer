#pragma once

#include "entity_type.hpp"
#include "tile.hpp"
#include "tile_id.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_object_t;
}  // namespace detail

struct tile_object final
{
  using entity = entity_type<detail::tile_object_t>;
  tile::entity tile {null<comp::tile>()};
};

}  // namespace wanderer::comp
