#include "make_renderer.hpp"

#include "game_constants.hpp"
#include "menu_constants.hpp"

namespace wanderer {

auto make_renderer(const cen::window& window) -> cen::renderer
{
  const auto flags = static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_TARGETTEXTURE);
  cen::renderer renderer{window, flags};

  renderer.set_blend_mode(cen::blend_mode::blend);

  const auto* typewriter = "resources/fonts/type_writer.ttf";
  renderer.emplace_font(glob::menu_font_s, typewriter, 8);
  renderer.emplace_font(glob::menu_font_m, typewriter, 16);
  renderer.emplace_font(glob::menu_font_l, typewriter, 24);

  renderer.set_logical_size(glob::logical_size<>);
  renderer.set_logical_integer_scale(true);

  return renderer;
}

}  // namespace wanderer
