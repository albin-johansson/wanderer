/**
 * @brief Provides the `ImageCache` alias.
 * @file image_cache.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <texture.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @typedef ImageCache
 * @brief Used for caches that store centurion textures.
 */
using image_cache = entt::cache<cen::texture>;

}  // namespace wanderer
