#pragma once

#include <renderer.h>

#include "image_cache.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::humanoid {

entt::entity add_player(entt::registry& registry,
                        centurion::Renderer& renderer,
                        ImageCache& imageCache);

entt::entity add_skeleton(entt::registry& registry,
                          centurion::Renderer& renderer,
                          ImageCache& imageCache);

}  // namespace wanderer::system::humanoid
