#pragma once

namespace wanderer {

/// \brief Provides identifiers for all of the different game menus.
/// \ingroup core
enum class menu_id
{
  in_game,   ///< The in-game "menu", i.e. the menu active when the game is played.
  home,      ///< The home (or start) menu.
  settings,  ///< The settings menu.
  saves,     ///< The saves management menu.
  controls   ///< The controls configuration menu.
};

}  // namespace wanderer
