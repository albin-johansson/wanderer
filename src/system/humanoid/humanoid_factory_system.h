#pragma once

#include <renderer.hpp>

#include "image_cache.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::humanoid {

auto add_player(entt::registry& registry,
                cen::renderer& renderer,
                image_cache& imageCache) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> entt::entity;

}  // namespace wanderer::sys::humanoid
