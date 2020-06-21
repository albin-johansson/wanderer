#pragma once

#include <renderer.h>

#include <string_view>

#include "image_cache.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] TilemapEntity make_map(entt::registry& registry,
                                     std::string_view map,
                                     centurion::Renderer& renderer,
                                     ImageCache& imageCache);

}
