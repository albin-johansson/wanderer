#pragma once

namespace wanderer {

/// \brief Provides identifiers for all of the different game menus.
/// \ingroup core
enum class MenuId
{
  InGame,     ///< The in-game "menu", i.e. the menu active when the game is played.
  Home,       ///< The home (or start) menu.
  Settings,   ///< The settings menu.
  Saves,      ///< The saves management menu.
  Controls,   ///< The controls configuration menu.
  DevConsole  ///< The developer console "menu".
};

}  // namespace wanderer
