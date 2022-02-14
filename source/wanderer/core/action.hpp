#pragma once

namespace wanderer {

enum class action_id
{
  noop,  ///< Do nothing.
  quit,  ///< Quit the game.

  goto_game,          ///< Play the game (enter the in-game "menu").
  goto_main_menu,     ///< Go to the main menu.
  goto_options_menu,  ///< Go to the options menu.
  goto_credits_menu,  ///< Go to the options menu.

  toggle_fullscreen  ///< Toggle fullscreen window mode.
};

}  // namespace wanderer