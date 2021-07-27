#include "line_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/line.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_lines(const entt::registry& registry, graphics_context& graphics)
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;

  auto& renderer = graphics.renderer();
  renderer.set_color(cen::colors::white);

  for (auto&& [entity, line, associated] :
       registry.view<comp::line, comp::associated_menu>().each())
  {
    if (associated.entity == menuEntity)
    {
      renderer.draw_line(from_grid(line.start), from_grid(line.end));
    }
  }
}

}  // namespace wanderer::sys
