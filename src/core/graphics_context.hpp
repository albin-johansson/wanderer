#pragma once

#include <cassert>        // assert
#include <centurion.hpp>  // renderer, texture
#include <cstddef>        // size_t
#include <functional>     // less
#include <map>            // map
#include <string>         // string
#include <vector>         // vector

#include "core/aliases/texture_id.hpp"
#include "core/aliases/texture_index.hpp"

namespace wanderer {

class graphics_context final
{
 public:
  explicit graphics_context(const cen::window& window);

  auto load(texture_id id, std::string path) -> texture_index;

  // Convenience function for rendering indexed textures
  void render(const texture_index index,
              const cen::irect& src,
              const cen::frect& dst) noexcept
  {
    m_renderer.render_t(find(index), src, dst);
  }

  [[nodiscard]] auto to_index(const texture_id id) const -> texture_index
  {
    return m_identifiers.at(id);
  }

  // Very fast index-based lookup
  [[nodiscard]] auto find(const texture_index index) const noexcept -> const cen::texture&
  {
    assert(index < m_textures.size());  // texture_index is unsigned
    return m_textures[index];
  }

  [[nodiscard]] auto small_font_cache() noexcept -> cen::font_cache&
  {
    return m_smallFontCache;
  }

  [[nodiscard]] auto light_canvas() noexcept -> cen::texture&
  {
    return m_lightCanvas;
  }

  [[nodiscard]] auto renderer() noexcept -> cen::renderer&
  {
    return m_renderer;
  }

 private:
  cen::renderer m_renderer;
  std::vector<cen::texture> m_textures;

  cen::font_cache m_smallFontCache;

  // Used as a rendering target for simulating lights
  cen::texture m_lightCanvas;

  // We store used IDs so that we avoid loading the same texture more than once
  std::map<texture_id, texture_index, std::less<>> m_identifiers;
};

}  // namespace wanderer
