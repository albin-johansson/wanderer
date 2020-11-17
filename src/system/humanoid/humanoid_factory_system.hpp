#pragma once

#include <abby.hpp>
#include <cen/renderer.hpp>
#include <entt.hpp>

#include "aabb_tree.hpp"
#include "level.hpp"
#include "texture_cache.hpp"
#include "vector2.hpp"

namespace wanderer::sys::humanoid {

auto add_player(entt::registry& registry,
                aabb_tree& tree,
                const vector2f& position,
                cen::renderer& renderer,
                texture_cache& cache) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  aabb_tree& tree,
                  const vector2f& position,
                  cen::renderer& renderer,
                  texture_cache& cache) -> entt::entity;

}  // namespace wanderer::sys::humanoid
