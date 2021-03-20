#include "line_rendering_system.hpp"

namespace wanderer::sys {

void render_lines(const entt::registry& registry,
                  cen::renderer& renderer,
                  const comp::line_pack& pack)
{
  renderer.set_color(cen::colors::white);

  for (const auto entity : pack.lines)
  {
    const auto& line = registry.get<comp::line>(entity);
    renderer.draw_line(line.start, line.end);
  }
}

}  // namespace wanderer::sys
