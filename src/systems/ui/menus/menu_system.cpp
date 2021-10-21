#include "menu_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "events/menu_events.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"

namespace wanderer::sys {

void UpdateMenu(entt::registry& registry,
                entt::dispatcher& dispatcher,
                const rune::input& input)
{
  const auto menuEntity = registry.ctx<ctx::ActiveMenu>().entity;

  if (const auto button = UpdateButtonHover(registry, input.mouse)) {
    if (QueryButton(registry, dispatcher, *button, input.mouse)) {
      if (auto* group = registry.try_get<comp::ButtonGroup>(menuEntity)) {
        if (sys::InButtonGroup(group->buttons, *button)) {
          group->selected = *button;
        }
      }
    }
  }
  else {
    cen::cursor::reset();
  }

  for (auto&& [entity, bind, associated] :
       registry.view<comp::KeyBind, comp::AssociatedMenu>().each())
  {
    if (associated.entity == menuEntity && input.keyboard.just_released(bind.key)) {
      dispatcher.enqueue<button_pressed_event>(bind.action);
    }
  }
}

void SwitchMenu(entt::registry& registry, entt::dispatcher& dispatcher, MenuId id)
{
  registry.unset<ctx::ActiveMenu>();

  for (auto&& [entity, menu] : registry.view<comp::Menu>().each()) {
    if (menu.id == id) {
      registry.set<ctx::ActiveMenu>(entity);
      dispatcher.trigger<menu_switched_event>(entity);
    }
  }
}

auto IsCurrentMenuBlocking(const entt::registry& registry) -> bool
{
  const auto menuEntity = registry.ctx<ctx::ActiveMenu>().entity;
  return registry.get<comp::Menu>(menuEntity).blocking;
}

}  // namespace wanderer::sys
