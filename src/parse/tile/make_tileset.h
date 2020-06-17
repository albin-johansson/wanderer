#pragma once

#include <renderer.h>
#include <step.h>

#include <vector>

#include "image_cache.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] entt::entity make_tileset(
    entt::registry& registry,
    const std::vector<step::Tileset>& tilesets,
    centurion::Renderer& renderer,
    ImageCache& imageCache);

}
