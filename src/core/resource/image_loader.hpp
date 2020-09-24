#pragma once

#include <entt.hpp>
#include <memory>  // shared_ptr
#include <renderer.hpp>
#include <string_view>  // string_view
#include <texture.hpp>

namespace wanderer {

/**
 * @class image_loader
 *
 * @brief Used as a factory for creating textures.
 *
 * @details This class is responsible for creating textures and should be the
 * way to load textures in combination with `image_cache` caches.
 *
 * @headerfile image_loader.hpp
 */
class image_loader final : public entt::loader<image_loader, cen::texture>
{
 public:
  /**
   * @brief Creates and returns a texture.
   *
   * @param renderer the renderer used to create the texture.
   * @param path the path of the image that will be loaded.
   *
   * @return a shared pointer to a texture.
   */
  [[nodiscard]] auto load(cen::renderer& renderer, std::string_view path) const
      -> std::shared_ptr<cen::texture>;
};

}  // namespace wanderer
