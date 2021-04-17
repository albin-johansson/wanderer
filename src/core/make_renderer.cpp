#include "make_renderer.hpp"

#include "core/game_constants.hpp"
#include "core/menu_constants.hpp"
#include "core/resources/resources.hpp"

namespace wanderer {

auto make_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window,
                         cen::renderer::accelerated | cen::renderer::target_textures};
  renderer.set_blend_mode(cen::blend_mode::blend);

  const auto typeWriter = resources::font("type_writer.ttf");
  renderer.emplace_font(glob::menu_font_s, typeWriter, 8);
  renderer.emplace_font(glob::menu_font_m, typeWriter, 16);
  renderer.emplace_font(glob::menu_font_l, typeWriter, 24);

  renderer.set_logical_size(glob::logical_size<>);
  renderer.set_logical_integer_scale(true);

  return renderer;
}

}  // namespace wanderer
