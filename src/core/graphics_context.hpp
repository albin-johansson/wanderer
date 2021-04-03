#pragma once

#include <centurion.hpp>  // renderer, texture
#include <cstddef>        // size_t
#include <functional>     // less
#include <map>            // map
#include <string>         // string
#include <vector>         // vector

#include "texture_handle.hpp"
#include "texture_id.hpp"
#include "texture_index.hpp"

namespace wanderer {

class graphics_context final
{
 public:
  explicit graphics_context(const cen::window& window);

  void render(texture_index index, const cen::irect& src, const cen::frect& dst) noexcept;

  auto load(texture_id id, const std::string& path) -> texture_index;

  [[nodiscard]] auto to_index(texture_id id) const -> texture_index;

  // Very fast index-based lookup
  [[nodiscard]] auto find(texture_index index) const noexcept -> const cen::texture&;

  [[nodiscard]] auto pixel_format() const noexcept -> cen::pixel_format
  {
    return m_format;
  }

  [[nodiscard]] auto small_font_cache() -> cen::font_cache&
  {
    return m_smallFontCache;
  }

  [[nodiscard]] auto renderer() noexcept -> cen::renderer&
  {
    return m_renderer;
  }

 private:
  cen::renderer m_renderer;
  std::vector<cen::texture> m_textures;
  cen::pixel_format m_format;

  cen::font_cache m_smallFontCache;
  // We store used IDs so that we avoid loading the same texture more than once
  std::map<texture_id, texture_index, std::less<>> m_identifiers;
};

}  // namespace wanderer
