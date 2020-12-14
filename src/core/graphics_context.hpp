#pragma once

#include <cen/renderer.hpp>
#include <cen/window.hpp>

#include "texture_cache.hpp"
#include "texture_handle.hpp"
#include "texture_loader.hpp"

namespace wanderer {

class graphics_context final
{
 public:
  explicit graphics_context(const cen::window& window);

  auto load_texture(const entt::id_type id, cen::czstring path)
      -> texture_handle
  {
    return m_textures.load<texture_loader>(id, m_renderer, path);
  }

  [[nodiscard]] auto renderer() noexcept -> cen::renderer&
  {
    return m_renderer;
  }

 private:
  cen::renderer m_renderer;
  texture_cache m_textures;
};

}  // namespace wanderer
