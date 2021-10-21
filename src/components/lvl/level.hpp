#pragma once

#include <entt.hpp>  // registry, entity, null

#include "wanderer_std.hpp"

namespace wanderer::comp {

// TODO consider removing this component and using context variables for the rest
struct Level final
{
  Level() = default;
  Level(Level&&) noexcept = default;
  Level& operator=(Level&&) noexcept = default;

  MapID id;

  entt::registry registry;
  aabb_tree tree;

  entt::entity tilemap{entt::null};
  entt::entity tileset{entt::null};

  maybe<float2> player_spawn_position;
};

struct OutsideLevel final
{};

struct ActiveLevel final
{};

}  // namespace wanderer::comp
