#include "graphics_context.hpp"

#include <utility>  // move

#include "core/menu_constants.hpp"
#include "core/resources.hpp"
#include "make_renderer.hpp"

namespace wanderer {
namespace {
inline const auto font_path = resources::font("type_writer.ttf");
}  // namespace

graphics_context::graphics_context(const cen::window& window)
    : rune::graphics{window}
    , m_lightCanvas{renderer(),
                    format(),
                    cen::texture_access::target,
                    glob::logical_size<>}
{
  reserve(10);

  auto& ren = renderer();
  ren.set_blend_mode(cen::blend_mode::blend);

  ren.emplace_font(glob::menu_font_s, font_path, glob::small_font_size);
  ren.emplace_font(glob::menu_font_m, font_path, glob::medium_font_size);
  ren.emplace_font(glob::menu_font_l, font_path, glob::large_font_size);

  ren.set_logical_size(glob::logical_size<>);
  ren.set_logical_integer_scaling(true);

  emplace_cache(small_font, font_path, glob::small_font_size);
  emplace_cache(medium_font, font_path, glob::medium_font_size);
  emplace_cache(large_font, font_path, glob::large_font_size);

  ren.set_color(cen::colors::white);

  get_cache(small_font).add_latin1(ren);
  get_cache(medium_font).add_latin1(ren);
  get_cache(large_font).add_latin1(ren);

  m_lightCanvas.set_blend_mode(cen::blend_mode::mod);
}

}  // namespace wanderer
