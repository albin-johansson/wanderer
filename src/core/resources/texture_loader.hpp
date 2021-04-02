#pragma once

#include <centurion.hpp>
#include <entt.hpp>
#include <memory>  // shared_ptr

namespace wanderer {

/**
 * \class texture_loader
 *
 * \brief Used as a factory for creating textures.
 *
 * \details This class is responsible for creating textures and should be the
 * way to load textures in combination with `image_cache` caches.
 *
 * \headerfile texture_loader.hpp
 */
class texture_loader final : public entt::resource_loader<texture_loader, cen::texture>
{
 public:
  /**
   * \brief Creates and returns a texture.
   *
   * \param renderer the renderer used to create the texture.
   * \param path the path of the image that will be loaded.
   *
   * \return a shared pointer to a texture.
   */
  [[nodiscard]] static auto load(cen::renderer& renderer, cen::czstring path)
      -> std::shared_ptr<cen::texture>
  {
    return std::make_shared<cen::texture>(renderer, path);
  }
};

}  // namespace wanderer
