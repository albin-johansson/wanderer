#include "button_system.hpp"

#include "checkbox.hpp"
#include "cursors.hpp"
#include "registry_utils.hpp"

namespace wanderer::sys {

void query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const comp::button::entity buttonEntity,
                  const cen::mouse_state& mouseState)
{
  auto& button = registry.get<comp::button>(buttonEntity);
  if (button.hover)
  {
    auto& cursors = singleton<comp::cursors>(registry);
    cursors.data.at(cen::system_cursor::hand).enable();

    if (mouseState.was_left_button_released())
    {
      if (button.action)
      {
        button.action->execute(dispatcher);
        button.hover = false;
        cen::cursor::reset();
      }
    }
  }
}

auto update_button_hover(entt::registry& registry,
                         const comp::menu::entity menuEntity,
                         const cen::mouse_state& mouseState)
    -> maybe<comp::button::entity>
{
  maybe<comp::button::entity> hoverButton;
  const auto mousePos = cen::cast<cen::fpoint>(mouseState.mouse_pos());

  if (const auto* buttonPack = registry.try_get<comp::button_pack>(menuEntity))
  {
    for (const auto entity : buttonPack->buttons)
    {
      auto& button = registry.get<comp::button>(entity);
      const auto& drawable = registry.get<comp::button_drawable>(entity);

      button.hover = drawable.bounds.contains(mousePos);
      if (button.hover)
      {
        hoverButton = entity;
      }
    }
  }

  if (const auto* buttonPack =
          registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    for (const auto entity : buttonPack->checkboxes)
    {
      auto& button = registry.get<comp::button>(entity);
      const auto& drawable = registry.get<comp::button_drawable>(entity);

      button.hover = drawable.bounds.contains(mousePos);
      if (button.hover)
      {
        hoverButton = comp::button::entity{entity.get()};
      }
    }
  }

  return hoverButton;
}

}  // namespace wanderer::sys
