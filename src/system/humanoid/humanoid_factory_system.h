#pragma once

#include <renderer.h>

#include "image_cache.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::humanoid {

auto add_player(entt::registry& registry,
                ctn::Renderer& renderer,
                ImageCache& imageCache) -> entt::entity;

auto add_skeleton(entt::registry& registry,
                  ctn::Renderer& renderer,
                  ImageCache& imageCache) -> entt::entity;

}  // namespace wanderer::system::humanoid
