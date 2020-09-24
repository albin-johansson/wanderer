#pragma once

#include <entt.hpp>
#include <renderer.hpp>

#include "image_cache.hpp"

namespace wanderer::sys::humanoid {

auto add_player(entt::registry& registry,
                cen::renderer& renderer,
                image_cache& imageCache) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> entt::entity;

}  // namespace wanderer::sys::humanoid
