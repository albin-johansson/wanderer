#include "in_game_menu_factory_system.hpp"

#include "components/key_bind.hpp"
#include "core/menu_action.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {

auto make_in_game_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, std::string{}, menu_id::in_game, false);
  registry.set<comp::in_game_menu>(entity);

  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
