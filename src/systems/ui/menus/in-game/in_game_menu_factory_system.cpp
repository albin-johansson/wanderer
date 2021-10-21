#include "in_game_menu_factory_system.hpp"

#include "components/key_bind.hpp"
#include "core/menu_action.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {

auto MakeInGameMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, std::string{}, MenuId::InGame, false);
  registry.set<comp::InGameMenu>(entity);

  AddBinds(registry, entity, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

}  // namespace wanderer::sys
