#include "home_menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/associated_menu.hpp"
#include "components/ui/button.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const entt::entity entity)
{
  const auto button = [&](std::string text,
                          const MenuAction action,
                          const float row,
                          const float col = -1) {
    const auto button =
        MakeButton(registry, std::move(text), action, GridPosition{row, col});

    auto& associated = registry.emplace<comp::AssociatedMenu>(button);
    associated.entity = entity;
  };

  float row = 5;

  button("Play", MenuAction::GotoInGame, row++);

  ++row;

  button("Quick Save", MenuAction::QuickSave, row++);
  button("Saves", MenuAction::GotoSaves, row++);
  button("Settings", MenuAction::GotoSettings, row++);
  button("Controls", MenuAction::GotoControls, row++);

  row += 2;

  button("Quit", MenuAction::Quit, row);
}

}  // namespace

auto make_home_menu(entt::registry& registry) -> entt::entity
{
  const auto entity = make_menu(registry, "Wanderer", MenuId::Home);
  registry.set<comp::HomeMenu>(entity);

  add_buttons(registry, entity);
  AddBinds(registry,
           entity,
           comp::KeyBind{cen::scancodes::escape, MenuAction::GotoInGame});

  return entity;
}

}  // namespace wanderer::sys
