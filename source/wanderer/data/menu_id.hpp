#pragma once

namespace wanderer {

/**
 * \brief Represents the available game menus.
 */
enum class MenuId
{
  game,     ///< In-game menu.
  home,     ///< Main menu.
  options,  ///< Options menu.
  saves,    ///< Saves menu.
  credits,  ///< Credits menu.
};

}  // namespace wanderer
