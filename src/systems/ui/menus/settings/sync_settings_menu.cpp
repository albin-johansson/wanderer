#include "button.hpp"
#include "checkbox.hpp"
#include "menu_system.hpp"
#include "settings.hpp"

namespace wanderer::sys {

void sync_settings_menu(entt::registry& registry)
{
  const auto& settings = registry.ctx<ctx::settings>();

  const auto view = registry.view<const comp::button, comp::checkbox>();
  for (auto&& [entity, button, checkbox] : view.each())
  {
    if (button.action == menu_action::toggle_fullscreen)
    {
      checkbox.checked = settings.fullscreen;
    }
    else if (button.action == menu_action::toggle_integer_scaling)
    {
      checkbox.checked = settings.integerScaling;
    }
    else if (button.action == menu_action::toggle_lights)
    {
      checkbox.checked = settings.simulateLights;
    }
  }
}

}  // namespace wanderer::sys