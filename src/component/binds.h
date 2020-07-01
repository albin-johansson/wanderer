/**
 * @brief Provides the `Binds` component.
 * @file binds.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <key.h>

#include "wanderer_stdinc.h"

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
 * @headerfile binds.h
 */
struct Binds final {
  ctn::Key up{SDL_SCANCODE_W};
  ctn::Key right{SDL_SCANCODE_D};
  ctn::Key down{SDL_SCANCODE_S};
  ctn::Key left{SDL_SCANCODE_A};
  ctn::Key attack{SDL_SCANCODE_SPACE};
};

}  // namespace wanderer::comp
