#include "graphics_context.hpp"

#include <utility>  // move

#include "core/resources.hpp"

namespace wanderer {
namespace {
inline const auto font_path = resources::font("type_writer.ttf");
}  // namespace

graphics_context::graphics_context(const cen::window& window)
    : rune::graphics{window}
    , m_lightCanvas{get_renderer(),
                    format(),
                    cen::texture_access::target,
                    glob::logical_size<>}
{
  reserve(10);

  auto& renderer = get_renderer();
  renderer.set_blend_mode(cen::blend_mode::blend);

  renderer.emplace_font(glob::menu_font_s, font_path, glob::small_font_size);
  renderer.emplace_font(glob::menu_font_m, font_path, glob::medium_font_size);
  renderer.emplace_font(glob::menu_font_l, font_path, glob::large_font_size);

  renderer.set_logical_size(glob::logical_size<>);
  renderer.set_logical_integer_scaling(true);

  emplace_cache(small_black_font, font_path, glob::small_font_size);

  emplace_cache(small_font, font_path, glob::small_font_size);
  emplace_cache(medium_font, font_path, glob::medium_font_size);
  emplace_cache(large_font, font_path, glob::large_font_size);

  renderer.set_color(cen::colors::black);
  get_cache(small_black_font).add_latin1(renderer);

  renderer.set_color(cen::colors::white);
  get_cache(small_font).add_latin1(renderer);
  get_cache(medium_font).add_latin1(renderer);
  get_cache(large_font).add_latin1(renderer);

  m_lightCanvas.set_blend_mode(cen::blend_mode::mul);
}

}  // namespace wanderer
