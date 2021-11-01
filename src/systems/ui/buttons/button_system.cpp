#include "button_system.hpp"

#include <cassert>  // assert

#include "components/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "events/menu_events.hpp"
#include "systems/ui/cursor_system.hpp"

namespace wanderer::sys {

void SetVisible(comp::Button& button, const bool visible)
{
  if (visible) {
    button.state |= comp::Button::visible_bit;
  }
  else {
    button.state &= ~comp::Button::visible_bit;
  }
}

void SetHovered(comp::Button& button, const bool hovered)
{
  if (hovered) {
    button.state |= comp::Button::hover_bit;
  }
  else {
    button.state &= ~comp::Button::hover_bit;
  }
}

void SetEnabled(comp::Button& button, const bool enabled)
{
  if (enabled) {
    button.state |= comp::Button::enable_bit;
  }
  else {
    button.state &= ~comp::Button::enable_bit;
  }
}

auto QueryButton(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const entt::entity buttonEntity,
                 const cen::mouse& mouse) -> bool
{
  assert(registry.all_of<comp::Button>(buttonEntity));
  auto& button = registry.get<comp::Button>(buttonEntity);
  if ((button.state & comp::Button::hover_bit) &&
      (button.state & comp::Button::enable_bit)) {
    EnableCursor(registry, cen::system_cursor::hand);

    if (mouse.was_left_button_released()) {
      dispatcher.enqueue<ButtonPressedEvent>(button.action);
      SetHovered(button, false);

      if (auto* checkbox = registry.try_get<comp::Checkbox>(buttonEntity)) {
        checkbox->checked = !checkbox->checked;
      }

      cen::cursor::reset();
      return true;
    }
  }

  return false;
}

auto UpdateButtonHover(entt::registry& registry, const cen::mouse& mouse)
    -> maybe<entt::entity>
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  for (auto&& [entity, button, associated] :
       registry.view<comp::Button, comp::AssociatedMenu>().each())
  {
    if (associated.entity == menuEntity) {
      if (button.state & comp::Button::visible_bit) {
        const auto& drawable = registry.get<comp::ButtonDrawable>(entity);

        const auto hovered = drawable.bounds.contains(mousePos);
        SetHovered(button, hovered);

        if (hovered) {
          return entity;
        }
      }
    }
  }

  return std::nullopt;
}

}  // namespace wanderer::sys
