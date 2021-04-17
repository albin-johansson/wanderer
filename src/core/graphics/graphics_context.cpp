#include "graphics_context.hpp"

#include <utility>  // move

#include "core/menu_constants.hpp"
#include "core/resources.hpp"
#include "make_renderer.hpp"

namespace wanderer {
namespace {
inline const auto font_path = resources::font("type_writer.ttf");
}

graphics_context::graphics_context(const cen::window& window)
    : m_renderer{make_renderer(window)}
    , m_smallFontCache{font_path, glob::small_font_size}
    , m_mediumFontCache{font_path, glob::medium_font_size}
    , m_largeFontCache{font_path, glob::large_font_size}
    , m_lightCanvas{m_renderer,
                    window.get_pixel_format(),
                    cen::texture_access::target,
                    glob::logical_size<>}
{
  m_textures.reserve(10);

  m_renderer.set_color(cen::colors::white);
  m_smallFontCache.add_latin1(m_renderer);
}

auto graphics_context::load(const texture_id id, std::string path) -> texture_index
{
  if (const auto it = m_identifiers.find(id); it != m_identifiers.end())
  {
    return it->second;
  }
  else
  {
    const auto index = m_textures.size();

    m_textures.emplace_back(m_renderer, std::move(path));
    m_identifiers.try_emplace(id, index);

    return texture_index{index};
  }
}

}  // namespace wanderer
