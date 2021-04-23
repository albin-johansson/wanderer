#include "button_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/cursors.hpp"
#include "events/button_pressed_event.hpp"
#include "systems/ui/cursor_system.hpp"

namespace wanderer::sys {
namespace {

template <typename T>
[[nodiscard]] auto check(entt::registry& registry,
                         const std::vector<T>& buttons,
                         const cen::fpoint& mousePos) -> maybe<comp::button::entity>
{
  for (const auto entity : buttons)
  {
    auto& button = registry.get<comp::button>(entity);
    const auto& drawable = registry.get<comp::button_drawable>(entity);

    if (button.visible)
    {
      button.hover = drawable.bounds.contains(mousePos);
      if (button.hover)
      {
        return comp::button::entity{entity.get()};
      }
    }
  }

  return std::nullopt;
}

}  // namespace

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

  if (const auto* buttonPack = registry.try_get<comp::button_pack>(menuEntity))
  {
    if (const auto button = check(registry, buttonPack->buttons, mousePos))
    {
      return button;
    }
  }

  if (const auto* group = registry.try_get<comp::button_group>(menuEntity))
  {
    if (const auto button = check(registry, group->buttons, mousePos))
    {
      return button;
    }
  }

  if (const auto* buttonPack = registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    if (const auto button = check(registry, buttonPack->checkboxes, mousePos))
    {
      return button;
    }
  }

  return std::nullopt;
}

}  // namespace wanderer::sys
