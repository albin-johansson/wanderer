#include "line_rendering_system.hpp"

#include "components/ui/associated_menu.hpp"
#include "components/ui/line.hpp"
#include "components/ui/menu.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void RenderLines(const entt::registry& registry, GraphicsContext& graphics)
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;

  auto& renderer = graphics.GetRenderer();
  renderer.set_color(cen::colors::white);

  for (auto&& [entity, line, associated] :
       registry.view<comp::Line, comp::AssociatedMenu>().each())
  {
    if (associated.entity == menuEntity) {
      renderer.draw_line(FromGrid(line.start), FromGrid(line.end));
    }
  }
}

}  // namespace wanderer::sys
