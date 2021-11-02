#include "menu_system.hpp"

#include "components/cursors.hpp"
#include "components/settings.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/button.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "events/menu_events.hpp"
#include "systems/ui/buttons/button_system.hpp"

namespace wanderer::sys {

void UpdateMenu(entt::registry& registry,
                entt::dispatcher& dispatcher,
                const cen::keyboard& keyboard,
                const cen::mouse& mouse)
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;

  if (const auto button = UpdateButtonHover(registry, mouse)) {
    if (QueryButton(registry, dispatcher, *button, mouse)) {
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
    if (associated.entity == menuEntity && keyboard.just_released(bind.key)) {
      dispatcher.enqueue<ButtonPressedEvent>(bind.action);
    }
  }
}

void SwitchMenu(entt::registry& registry, entt::dispatcher& dispatcher, MenuId id)
{
  registry.unset<ActiveMenu>();

  for (auto&& [entity, menu] : registry.view<comp::Menu>().each()) {
    if (menu.id == id) {
      registry.set<ActiveMenu>(entity);
      dispatcher.trigger<MenuSwitchedEvent>(entity);
    }
  }
}

void SyncSettingsMenu(entt::registry& registry)
{
  const auto& settings = registry.ctx<ctx::Settings>();

  for (auto&& [entity, button, checkbox] :
       registry.view<const comp::Button, comp::Checkbox>().each())
  {
    if (button.action == MenuAction::ToggleFullscreen) {
      checkbox.checked = settings.fullscreen;
    }
    else if (button.action == MenuAction::ToggleIntegerScaling) {
      checkbox.checked = settings.integer_scaling;
    }
  }
}

auto IsMenuActive(const entt::registry& shared, const MenuId id) -> bool
{
  const auto menuEntity = shared.ctx<ActiveMenu>().entity;
  return shared.get<comp::Menu>(menuEntity).id == id;
}

auto IsCurrentMenuBlocking(const entt::registry& registry) -> bool
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;
  return registry.get<comp::Menu>(menuEntity).blocking;
}

}  // namespace wanderer::sys
