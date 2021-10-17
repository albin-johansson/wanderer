#include "registry_system.hpp"

#include <centurion.hpp>  // system_cursor

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ctx/time_of_day.hpp"
#include "systems/ui/menus/controls/controls_menu_factory_system.hpp"
#include "systems/ui/menus/home/home_menu_factory_system.hpp"
#include "systems/ui/menus/in-game/in_game_menu_factory_system.hpp"
#include "systems/ui/menus/saves/saves_menu_factory_system.hpp"
#include "systems/ui/menus/settings/settings_menu_factory_system.hpp"

namespace wanderer::sys {

auto MakeSharedRegistry() -> entt::registry
{
  entt::registry registry;

  const auto home = make_home_menu(registry);
  make_in_game_menu(registry);
  make_controls_menu(registry);
  make_settings_menu(registry);
  make_saves_menu(registry);

  registry.set<ctx::ActiveMenu>(home);
  registry.set<ctx::TimeOfDay>();

  auto& cursors = registry.set<ctx::Cursors>();
  cursors.data.try_emplace(cen::system_cursor::hand, cen::system_cursor::hand);

  return registry;
}

}  // namespace wanderer::sys
