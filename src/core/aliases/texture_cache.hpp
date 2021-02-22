#pragma once

#include <cen/texture.hpp>
#include <entt.hpp>

namespace wanderer {

/**
 * \typedef texture_cache
 *
 * \brief Used for caches that store centurion textures.
 */
using texture_cache = entt::resource_cache<cen::texture>;

}  // namespace wanderer
