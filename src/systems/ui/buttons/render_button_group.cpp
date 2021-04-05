#include "button_system.hpp"

namespace wanderer::sys {

void render_button_group(const entt::registry& registry,
                         cen::renderer& renderer,
                         const comp::button_group& group)
{
  if (group.selected != entt::null)
  {
    const auto& button = registry.get<comp::button>(group.selected);
    const auto& drawable = registry.get<comp::button_drawable>(group.selected);
    renderer.set_color(cen::colors::dark_green);
    renderer.fill_rect(drawable.bounds);
  }

  for (const auto entity : group.buttons)
  {
    render_button(registry, renderer, entity);
  }
}

}  // namespace wanderer::sys
