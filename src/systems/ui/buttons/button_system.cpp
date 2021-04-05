#include "button_system.hpp"

#include "button_pressed_event.hpp"
#include "checkbox.hpp"
#include "cursors.hpp"

namespace wanderer::sys {

auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const comp::button::entity buttonEntity,
                  const cen::mouse& mouse) -> bool
{
  auto& button = registry.get<comp::button>(buttonEntity);
  if (button.hover)
  {
    auto& cursors = registry.ctx<comp::cursors>();
    cursors.data.at(cen::system_cursor::hand).enable();

    if (mouse.was_left_button_released())
    {
      dispatcher.enqueue<event::button_pressed>(button.action);
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

auto update_button_hover(entt::registry& registry,
                         const comp::menu::entity menuEntity,
                         const cen::mouse& mouse) -> maybe<comp::button::entity>
{
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  const auto check = [&](auto& buttons) -> maybe<comp::button::entity> {
    for (const auto entity : buttons)
    {
      auto& button = registry.get<comp::button>(entity);
      const auto& drawable = registry.get<comp::button_drawable>(entity);

      button.hover = drawable.bounds.contains(mousePos);
      if (button.hover)
      {
        return comp::button::entity{entity.get()};
      }
    }

    return std::nullopt;
  };

  if (const auto* buttonPack = registry.try_get<comp::button_pack>(menuEntity))
  {
    if (const auto button = check(buttonPack->buttons))
    {
      return button;
    }
  }

  if (const auto* group = registry.try_get<comp::button_group>(menuEntity))
  {
    if (const auto button = check(group->buttons))
    {
      return button;
    }
  }

  if (const auto* buttonPack = registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    if (const auto button = check(buttonPack->checkboxes))
    {
      return button;
    }
  }

  return std::nullopt;
}

}  // namespace wanderer::sys
