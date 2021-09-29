#include "button_system.hpp"

#include <cassert>  // assert

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "events/menu_events.hpp"
#include "systems/ui/cursor_system.hpp"

namespace wanderer::sys {

void set_visible(comp::button& button, const bool visible)
{
  if (visible) {
    button.state |= comp::button::visible_bit;
  }
  else {
    button.state &= ~comp::button::visible_bit;
  }
}

void set_hovered(comp::button& button, const bool hovered)
{
  if (hovered) {
    button.state |= comp::button::hover_bit;
  }
  else {
    button.state &= ~comp::button::hover_bit;
  }
}

void set_enabled(comp::button& button, const bool enabled)
{
  if (enabled) {
    button.state |= comp::button::enable_bit;
  }
  else {
    button.state &= ~comp::button::enable_bit;
  }
}

auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const entt::entity buttonEntity,
                  const cen::mouse& mouse) -> bool
{
  assert(registry.all_of<comp::button>(buttonEntity));
  auto& button = registry.get<comp::button>(buttonEntity);
  if ((button.state & comp::button::hover_bit) &&
      (button.state & comp::button::enable_bit)) {
    enable_cursor(registry, cen::system_cursor::hand);

    if (mouse.was_left_button_released()) {
      dispatcher.enqueue<button_pressed_event>(button.action);
      set_hovered(button, false);

      if (auto* checkbox = registry.try_get<comp::checkbox>(buttonEntity)) {
        checkbox->checked = !checkbox->checked;
      }

      cen::cursor::reset();
      return true;
    }
  }

  return false;
}

auto update_button_hover(entt::registry& registry, const cen::mouse& mouse)
    -> maybe<entt::entity>
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  for (auto&& [entity, button, associated] :
       registry.view<comp::button, comp::associated_menu>().each())
  {
    if (associated.entity == menuEntity) {
      if (button.state & comp::button::visible_bit) {
        const auto& drawable = registry.get<comp::button_drawable>(entity);

        const auto hovered = drawable.bounds.contains(mousePos);
        set_hovered(button, hovered);

        if (hovered) {
          return entity;
        }
      }
    }
  }

  return std::nullopt;
}

}  // namespace wanderer::sys
