#pragma once

#include "menu.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief Creates the main menu.
 *
 * \param cfg the game configuration that will be used.
 *
 * \return a menu.
 */
[[nodiscard]] auto make_main_menu(const game_cfg& cfg) -> ui_menu;

/**
 * \brief Creates the non-blocking in-game menu.
 *
 * \param cfg the game configuration that will be used.
 *
 * \return a menu.
 */
[[nodiscard]] auto make_in_game_menu(const game_cfg& cfg) -> ui_menu;

}  // namespace wanderer
