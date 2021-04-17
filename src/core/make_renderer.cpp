#include "make_renderer.hpp"

#include "core/game_constants.hpp"
#include "core/menu_constants.hpp"
#include "resources.hpp"

namespace wanderer {

auto make_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window,
                         cen::renderer::accelerated | cen::renderer::target_textures};
  renderer.set_blend_mode(cen::blend_mode::blend);

  const auto typeWriter = resources::font("type_writer.ttf");
  renderer.emplace_font(glob::menu_font_s, typeWriter, glob::small_font_size);
  renderer.emplace_font(glob::menu_font_m, typeWriter, glob::medium_font_size);
  renderer.emplace_font(glob::menu_font_l, typeWriter, glob::large_font_size);

  renderer.set_logical_size(glob::logical_size<>);
  renderer.set_logical_integer_scale(true);

  return renderer;
}

}  // namespace wanderer
