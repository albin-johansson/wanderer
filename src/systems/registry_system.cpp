#include "registry_system.hpp"

#include <centurion.hpp>  // system_cursor

#include "components/active_menu.hpp"
#include "components/cursors.hpp"
#include "components/time_of_day.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {

auto MakeSharedRegistry() -> entt::registry
{
  entt::registry registry;

  const auto home = MakeHomeMenu(registry);
  MakeInGameMenu(registry);
  MakeControlsMenu(registry);
  MakeSettingsMenu(registry);
  MakeSavesMenu(registry);

  registry.set<ctx::ActiveMenu>(home);
  registry.set<ctx::TimeOfDay>();

  auto& cursors = registry.set<ctx::Cursors>();
  cursors.data.try_emplace(cen::system_cursor::hand, cen::system_cursor::hand);

  return registry;
}

}  // namespace wanderer::sys
