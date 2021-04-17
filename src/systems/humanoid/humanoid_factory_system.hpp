#pragma once

#include <entt.hpp>  // registry, entity

#include "components/ctx/player.hpp"
#include "core/aliases/aabb_tree.hpp"
#include "core/aliases/float2.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/levels/level.hpp"

namespace wanderer::sys {

/// \name Humanoids
/// \{

auto add_player(entt::registry& registry,
                aabb_tree& tree,
                float2 position,
                graphics_context& graphics) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  aabb_tree& tree,
                  float2 position,
                  graphics_context& graphics) -> entt::entity;

/// \} End of humanoid

}  // namespace wanderer::sys
