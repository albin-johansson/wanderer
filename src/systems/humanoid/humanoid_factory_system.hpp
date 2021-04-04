#pragma once

#include <abby.hpp>
#include <entt.hpp>

#include "aabb_tree.hpp"
#include "float2.hpp"
#include "graphics_context.hpp"
#include "level.hpp"
#include "player.hpp"

namespace wanderer::sys {

auto add_player(entt::registry& registry,
                aabb_tree& tree,
                float2 position,
                graphics_context& graphics) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  aabb_tree& tree,
                  float2 position,
                  graphics_context& graphics) -> entt::entity;

}  // namespace wanderer::sys
