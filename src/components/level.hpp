#pragma once

#include <entt/entt.hpp>  // registry, entity, null

#include "wanderer_std.hpp"

namespace wanderer {

struct Level final
{
  Level() = default;
  Level(Level&&) noexcept = default;
  Level& operator=(Level&&) noexcept = default;

  MapID id;

  entt::registry registry;
  aabb_tree tree;

  entt::entity tileset{entt::null};

  Maybe<Vec2> player_spawn_position;
};

struct OutsideLevel final
{};

struct ActiveLevel final
{};

}  // namespace wanderer
