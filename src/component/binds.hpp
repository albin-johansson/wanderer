/**
 * @brief Provides the `Binds` component.
 * @file binds.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <key_code.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Binds
 * @brief Represents all of the key binds used by the player.
 *
 * @var Binds::up
 * The key associated with moving "up".
 * @var Binds::right
 * The key associated with moving "right".
 * @var Binds::down
 * The key associated with moving "down".
 * @var Binds::left
 * The key associated with moving "left".
 * @var Binds::attack
 * The key associated with triggering an attack.
 *
 * @headerfile binds.hpp
 */
struct Binds final {
  cen::key_code up{SDLK_w};
  cen::key_code right{SDLK_d};
  cen::key_code down{SDLK_s};
  cen::key_code left{SDLK_a};
  cen::key_code attack{SDLK_SPACE};
};

}  // namespace wanderer::comp
