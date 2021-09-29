#pragma once

#include <entt.hpp>  // registry, entity, null

#include "common/aabb_tree.hpp"
#include "common/float2.hpp"
#include "common/map_id.hpp"
#include "common/maybe.hpp"

namespace wanderer::comp {

struct level final
{
  level() = default;
  level(level&&) noexcept = default;
  level& operator=(level&&) noexcept = default;

  map_id id;

  entt::registry registry;
  aabb_tree tree;

  entt::entity tilemap{entt::null};
  entt::entity tileset{entt::null};

  maybe<float2> player_spawn_position;
};

struct outside_level final
{};

struct active_level final
{};

}  // namespace wanderer::comp
