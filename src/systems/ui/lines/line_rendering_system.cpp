#include "line_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/line.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_lines(const entt::registry& registry, GraphicsContext& graphics)
{
  const auto menuEntity = registry.ctx<ctx::ActiveMenu>().entity;

  auto& renderer = graphics.get_renderer();
  renderer.set_color(cen::colors::white);

  for (auto&& [entity, line, associated] :
       registry.view<comp::Line, comp::AssociatedMenu>().each())
  {
    if (associated.entity == menuEntity) {
      renderer.draw_line(from_grid(line.start), from_grid(line.end));
    }
  }
}

}  // namespace wanderer::sys
