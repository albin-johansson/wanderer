#include "menu_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ctx/time_of_day.hpp"
#include "events/button_pressed_event.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/menus/controls/controls_menu_factory_system.hpp"
#include "systems/ui/menus/home/home_menu_factory_system.hpp"
#include "systems/ui/menus/in-game/in_game_menu_factory_system.hpp"
#include "systems/ui/menus/saves/saves_menu_factory_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"
#include "systems/ui/menus/settings/settings_menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void query_binds(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 comp::key_bind_pack& pack,
                 const cen::keyboard& keys)
{
  for (const auto entity : pack.binds)
  {
    auto& bind = registry.get<comp::key_bind>(entity);
    if (keys.just_released(bind.key))
    {
      dispatcher.enqueue<button_pressed_event>(bind.action, 0u);
    }
  }
}

}  // namespace

auto make_menus() -> entt::registry
{
  entt::registry registry;

  const auto home = make_home_menu(registry);
  make_in_game_menu(registry);
  make_controls_menu(registry);
  make_settings_menu(registry);
  make_saves_menu(registry);

  registry.set<ctx::active_menu>(home);
  registry.set<ctx::time_of_day>();

  auto& cursors = registry.set<ctx::cursors>();
  cursors.data.try_emplace(cen::system_cursor::hand, cen::system_cursor::hand);

  return registry;
}

void update_menu(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const input& input)
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto& menu = registry.get<comp::menu>(menuEntity);

  if (const auto button = update_button_hover(registry, input.mouse))
  {
    if (query_button(registry, dispatcher, *button, input.mouse))
    {
      if (auto* group = registry.try_get<comp::button_group>(menuEntity))
      {
        if (sys::in_button_group(group->buttons, *button))
        {
          group->selected = *button;
        }
      }
    }
  }
  else
  {
    cen::cursor::reset();
  }

  if (auto* binds = registry.try_get<comp::key_bind_pack>(menuEntity))
  {
    query_binds(registry, dispatcher, *binds, input.keyboard);
  }
}

void switch_menu(entt::registry& registry, const menu_id id)
{
  registry.unset<ctx::active_menu>();

  for (auto&& [entity, menu] : registry.view<comp::menu>().each())
  {
    if (menu.id == id)
    {
      registry.set<ctx::active_menu>(comp::menu::entity{entity});

      if (menu.id == menu_id::saves)
      {
        update_saves_menu(registry);
      }
    }
  }
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto menuEntity = registry.ctx<const ctx::active_menu>().entity;
  return registry.get<comp::menu>(menuEntity).blocking;
}

}  // namespace wanderer::sys
