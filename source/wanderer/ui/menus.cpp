#include "menus.hpp"

#include "wanderer/data/cfg.hpp"

namespace wanderer {

auto make_main_menu(const game_cfg&) -> ui_menu
{
  ui_menu menu;
  menu.set_title("Wanderer");
  menu.set_blocking(true);

  menu.reserve_buttons(4);
  menu.add_button("Play", action_id::goto_game, {ui_button::centered, 150});

  menu.add_button("Options", action_id::noop, {ui_button::centered, 250});
  menu.add_button("Credits", action_id::noop, {ui_button::centered, 300});

  menu.add_button("Quit", action_id::quit, {ui_button::centered, 400});

  return menu;
}

auto make_in_game_menu(const game_cfg&) -> ui_menu
{
  ui_menu menu;
  menu.set_blocking(false);

  menu.reserve_buttons(1);
  menu.add_button("Pause", action_id::goto_main_menu, {6, 6});

  return menu;
}

}  // namespace wanderer