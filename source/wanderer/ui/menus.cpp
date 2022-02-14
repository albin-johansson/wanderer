#include "menus.hpp"

#include "wanderer/data/cfg.hpp"

namespace wanderer {

auto make_in_game_menu() -> ui_menu
{
  ui_menu menu;
  menu.set_blocking(false);

  menu.reserve_buttons(1);
  menu.add_button("Pause", action_id::goto_main_menu, {6, 6});

  return menu;
}

auto make_main_menu() -> ui_menu
{
  ui_menu menu;
  menu.set_title("Wanderer");
  menu.set_blocking(true);

  menu.reserve_buttons(4);
  menu.add_button("Play", action_id::goto_game, {ui_button::centered, 150});

  menu.add_button("Options", action_id::goto_options_menu, {ui_button::centered, 250});
  menu.add_button("Credits", action_id::goto_credits_menu, {ui_button::centered, 300});

  menu.add_button("Quit", action_id::quit, {ui_button::centered, 400});

  return menu;
}

auto make_options_menu() -> ui_menu
{
  ui_menu menu;
  menu.set_title("Options");
  menu.set_blocking(true);

  menu.add_button("Return", action_id::goto_main_menu, {ui_button::centered, 150});

  menu.add_button("Toggle Fullscreen",
                  action_id::toggle_fullscreen,
                  {ui_button::centered, 250});

  return menu;
}

auto make_credits_menu() -> ui_menu
{
  ui_menu menu;
  menu.set_title("Credits");
  menu.set_blocking(true);

  menu.add_button("Return", action_id::goto_main_menu, {ui_button::centered, 150});

  return menu;
}

}  // namespace wanderer