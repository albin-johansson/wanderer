/**
 * @brief Provides the `ImageLoader` class.
 * @file image_loader.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <memory>
#include <renderer.hpp>
#include <string_view>
#include <texture.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer {

/**
 * @class ImageLoader
 * @brief Used as a factory for creating textures.
 * @details This class is responsible for creating textures and should be the
 * way to load textures in combination with `image_cache` caches.
 *
 * @headerfile image_loader.hpp
 */
class ImageLoader final : public entt::loader<ImageLoader, cen::texture>
{
 public:
  /**
   * @brief Creates and returns a texture.
   * @param renderer the renderer used to create the texture.
   * @param path the path of the image that will be loaded.
   * @return a shared pointer to a texture.
   * @throws CenturionException if something goes wrong.
   */
  [[nodiscard]] auto load(cen::renderer& renderer, std::string_view path) const
      -> std::shared_ptr<cen::texture>;
};

}  // namespace wanderer
