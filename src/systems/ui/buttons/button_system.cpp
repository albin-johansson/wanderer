#include "button_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "events/button_pressed_event.hpp"
#include "systems/ui/cursor_system.hpp"

namespace wanderer::sys {

auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const comp::button::entity buttonEntity,
                  const cen::mouse& mouse) -> bool
{
  auto& button = registry.get<comp::button>(buttonEntity);
  if (button.hover && button.enabled)
  {
    enable_cursor(registry, cen::system_cursor::hand);

    if (mouse.was_left_button_released())
    {
      dispatcher.enqueue<button_pressed_event>(button.action);
      button.hover = false;

      if (auto* checkbox = registry.try_get<comp::checkbox>(buttonEntity))
      {
        checkbox->checked = !checkbox->checked;
      }

      cen::cursor::reset();
      return true;
    }
  }

  return false;
}

auto update_button_hover(entt::registry& registry, const cen::mouse& mouse)
    -> maybe<comp::button::entity>
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  for (auto&& [entity, button, associated] :
       registry.view<comp::button, comp::associated_menu>().each())
  {
    if (associated.entity == menuEntity)
    {
      auto& button = registry.get<comp::button>(entity);
      if (button.visible)
      {
        const auto& drawable = registry.get<comp::button_drawable>(entity);
        button.hover = drawable.bounds.contains(mousePos);
        if (button.hover)
        {
          return comp::button::entity{entity};
        }
      }
    }
  }

  return std::nullopt;
}

}  // namespace wanderer::sys
