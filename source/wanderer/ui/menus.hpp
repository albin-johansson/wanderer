#pragma once

#include "menu.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief Creates the non-blocking in-game menu.
 *
 * \return a menu.
 */
[[nodiscard]] auto make_in_game_menu() -> ui_menu;

/**
 * \brief Creates the main menu.
 *
 * \return a menu.
 */
[[nodiscard]] auto make_main_menu() -> ui_menu;

[[nodiscard]] auto make_options_menu() -> ui_menu;

[[nodiscard]] auto make_credits_menu() -> ui_menu;

}  // namespace wanderer
