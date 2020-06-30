#pragma once

#include <renderer.h>

#include <string_view>

#include "image_cache.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] auto make_map(entt::registry& registry,
                            std::string_view map,
                            ctn::Renderer& renderer,
                            ImageCache& imageCache) -> component::TilemapEntity;

}
