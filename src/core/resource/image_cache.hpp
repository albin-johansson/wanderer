#pragma once

#include <texture.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer {

/**
 * @typedef image_cache
 * @brief Used for caches that store centurion textures.
 */
using image_cache = entt::cache<cen::texture>;

}  // namespace wanderer
