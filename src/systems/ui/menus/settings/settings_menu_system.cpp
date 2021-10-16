#include "settings_menu_system.hpp"

#include "components/ctx/settings.hpp"
#include "components/ui/button.hpp"
#include "components/ui/checkbox.hpp"

namespace wanderer::sys {

void sync_settings_menu(entt::registry& registry)
{
  const auto& settings = registry.ctx<ctx::Settings>();

  for (auto&& [entity, button, checkbox] :
       registry.view<const comp::Button, comp::Checkbox>().each())
  {
    if (button.action == menu_action::toggle_fullscreen) {
      checkbox.checked = settings.fullscreen;
    }
    else if (button.action == menu_action::toggle_integer_scaling) {
      checkbox.checked = settings.integer_scaling;
    }
  }
}

}  // namespace wanderer::sys
