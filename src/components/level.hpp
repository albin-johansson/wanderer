#pragma once

#include <entt.hpp>  // registry

#include "components/tileset.hpp"
#include "core/aliases/aabb_tree.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/float2.hpp"
#include "core/aliases/maybe.hpp"
#include "core/ecs/null_entity.hpp"
#include "tilemap.hpp"

namespace wanderer::comp {

namespace tags {
struct level_tag;
}  // namespace tags

struct level final
{
  using entity = entity_type<tags::level_tag>;

  map_id id;

  entt::registry registry;
  aabb_tree tree;

  comp::tilemap::entity tilemap{null<comp::tilemap>()};
  comp::tileset::entity tileset{null<comp::tileset>()};

  maybe<float2> player_spawn_position;
};

struct active_level final
{};

}  // namespace wanderer::comp
