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

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  const auto button = [&](std::string text,
                          const menu_action action,
                          const float row,
                          const float col = -1) {
    const auto button =
        make_button(registry, std::move(text), action, grid_position{row, col});

    auto& associated = registry.emplace<comp::associated_menu>(button);
    associated.entity = entity;
  };

  float row = 5;

  button("Play", menu_action::goto_in_game, row++);

  ++row;

  button("Quick Save", menu_action::quick_save, row++);
  button("Saves", menu_action::goto_saves, row++);
  button("Settings", menu_action::goto_settings, row++);
  button("Controls", menu_action::goto_controls, row++);

  row += 2;

  button("Quit", menu_action::quit, row);
}

}  // namespace

auto make_home_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Wanderer", menu_id::home);
  registry.set<comp::home_menu>(entity);

  add_buttons(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_in_game});

  return entity;
}

}  // namespace wanderer::sys
