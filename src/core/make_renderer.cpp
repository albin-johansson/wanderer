#include "make_renderer.hpp"

#include <entt.hpp>

#include "game_constants.hpp"

namespace wanderer {

auto make_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window};

  const auto* typewriter = "resource/font/type_writer.ttf";
  renderer.emplace_font("typewriter_s"_hs, typewriter, 8);
  renderer.emplace_font("typewriter_m"_hs, typewriter, 16);
  renderer.emplace_font("typewriter_l"_hs, typewriter, 24);

  renderer.set_logical_size(glob::logicalSize<>);
  renderer.set_logical_integer_scale(true);

  return renderer;
}

}  // namespace wanderer
