#include "create_in_game_menu.hpp"

#include "key_bind.hpp"
#include "key_bind_system.hpp"
#include "menu_action.hpp"
#include "menu_factory_system.hpp"

namespace wanderer::sys {

auto create_in_game_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, std::string{}, menu_id::in_game, false);
  registry.set<comp::in_game_menu>(entity);

  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
