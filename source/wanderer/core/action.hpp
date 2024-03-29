#pragma once

namespace wanderer {

enum class Action
{
  noop,  ///< Do nothing.
  quit,  ///< Quit the game.

  goto_game,          ///< Play the game (enter the in-game "menu").
  goto_main_menu,     ///< Go to the main menu.
  goto_options_menu,  ///< Go to the options menu.
  goto_saves_menu,    ///< Go to the saves menu.
  goto_credits_menu,  ///< Go to the options menu.

  quick_save,  ///< Create a quick save.

  toggle_fullscreen,      ///< Toggle fullscreen window mode.
  toggle_vsync,           ///< Toggle VSync.
  toggle_integer_scaling  ///< Toggle integer scaling for logical viewports.
};

}  // namespace wanderer