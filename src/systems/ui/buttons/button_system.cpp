#include "button_system.hpp"

#include "button_pressed_event.hpp"
#include "checkbox.hpp"
#include "cursors.hpp"

namespace wanderer::sys {

void query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const comp::button::entity buttonEntity,
                  const cen::mouse& mouse)
{
  auto& button = registry.get<comp::button>(buttonEntity);
  if (button.hover)
  {
    auto& cursors = registry.ctx<comp::cursors>();
    cursors.data.at(cen::system_cursor::hand).enable();

    if (mouse.was_left_button_released())
    {
      dispatcher.enqueue<comp::button_pressed_event>(button.action);
      button.hover = false;

      if (auto* checkbox = registry.try_get<comp::checkbox>(buttonEntity))
      {
        checkbox->checked = !checkbox->checked;
      }

      cen::cursor::reset();
    }
  }
}

auto update_button_hover(entt::registry& registry,
                         const comp::menu::entity menuEntity,
                         const cen::mouse& mouse) -> maybe<comp::button::entity>
{
  maybe<comp::button::entity> hoverButton;
  const auto mousePos = cen::cast<cen::fpoint>(mouse.position());

  const auto check = [&](auto& buttons) {
    for (const auto entity : buttons)
    {
      auto& button = registry.get<comp::button>(entity);
      const auto& drawable = registry.get<comp::button_drawable>(entity);

      button.hover = drawable.bounds.contains(mousePos);
      if (button.hover)
      {
        hoverButton = comp::button::entity{entity.get()};
      }
    }
  };

  if (const auto* buttonPack = registry.try_get<comp::button_pack>(menuEntity))
  {
    check(buttonPack->buttons);
  }

  if (const auto* buttonPack =
          registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    check(buttonPack->checkboxes);
  }

  return hoverButton;
}

}  // namespace wanderer::sys
