#pragma once

#include <abby.hpp>
#include <cen/renderer.hpp>
#include <entt.hpp>

#include "image_cache.hpp"
#include "level.hpp"

namespace wanderer::sys::humanoid {

auto add_player(entt::registry& registry,
                abby::aabb_tree<entt::entity>& aabbTree,
                cen::renderer& renderer,
                image_cache& imageCache) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  abby::aabb_tree<entt::entity>& aabbTree,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> entt::entity;

}  // namespace wanderer::sys::humanoid
