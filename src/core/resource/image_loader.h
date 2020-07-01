/**
 * @brief Provides the `ImageLoader` class.
 * @file image_loader.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <renderer.h>
#include <texture.h>

#include <memory>
#include <string_view>

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @class ImageLoader
 * @brief Used as a factory for creating textures.
 * @details This class is responsible for creating textures and should be the
 * way to load textures in combination with `ImageCache` caches.
 *
 * @headerfile image_loader.h
 */
class ImageLoader final : public entt::loader<ImageLoader, ctn::Texture> {
 public:
  /**
   * @brief Creates and returns a texture.
   * @param renderer the renderer used to create the texture.
   * @param path the path of the image that will be loaded.
   * @return a shared pointer to a texture.
   * @throws CenturionException if something goes wrong.
   */
  [[nodiscard]] auto load(ctn::Renderer& renderer, std::string_view path) const
      -> std::shared_ptr<ctn::Texture>;
};

}  // namespace wanderer
