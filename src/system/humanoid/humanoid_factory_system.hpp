#pragma once

#include <entt.hpp>
#include <cen/renderer.hpp>

#include "aabb_tree.hpp"
#include "image_cache.hpp"
#include "level.hpp"

namespace wanderer::sys::humanoid {

auto add_player(level& level, cen::renderer& renderer, image_cache& imageCache)
    -> entt::entity;

auto add_skeleton(level& level,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> entt::entity;

}  // namespace wanderer::sys::humanoid
