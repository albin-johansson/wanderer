#include "button_system.hpp"

#include <cassert>  // assert

#include "components/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "events/menu_events.hpp"
#include "systems/ui/cursor_system.hpp"

namespace wanderer::sys {

void SetVisible(Button& button, const bool visible)
{
  if (visible) {
    button.state |= Button::visible_bit;
  }
  else {
    button.state &= ~Button::visible_bit;
  }
}

void SetHovered(Button& button, const bool hovered)
{
  if (hovered) {
    button.state |= Button::hover_bit;
  }
  else {
    button.state &= ~Button::hover_bit;
  }
}

void SetEnabled(Button& button, const bool enabled)
{
  if (enabled) {
    button.state |= Button::enable_bit;
  }
  else {
    button.state &= ~Button::enable_bit;
  }
}

auto QueryButton(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const entt::entity buttonEntity,
                 const cen::mouse& mouse) -> bool
{
  assert(registry.all_of<Button>(buttonEntity));
  auto& button = registry.get<Button>(buttonEntity);
  if ((button.state & Button::hover_bit) && (button.state & Button::enable_bit)) {
    EnableCursor(registry, cen::system_cursor::hand);

    if (mouse.was_left_button_released()) {
      dispatcher.enqueue<ButtonPressedEvent>(button.action);
      SetHovered(button, false);

      if (auto* checkbox = registry.try_get<Checkbox>(buttonEntity)) {
        checkbox->checked = !checkbox->checked;
      }

      cen::cursor::reset();
      return true;
    }
  }

  return false;
}

auto UpdateButtonHover(entt::registry& registry, const cen::mouse& mouse)
    -> Maybe<entt::entity>
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  for (auto&& [entity, button, associated] :
       registry.view<Button, AssociatedMenu>().each()) {
    if (associated.entity == menuEntity) {
      if (button.state & Button::visible_bit) {
        const auto& drawable = registry.get<ButtonDrawable>(entity);

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
