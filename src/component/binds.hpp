#pragma once

#include <key_code.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct binds
 * @brief Represents all of the key binds used by the player.
 *
 * @var binds::up
 * The key associated with moving "up".
 * @var binds::right
 * The key associated with moving "right".
 * @var binds::down
 * The key associated with moving "down".
 * @var binds::left
 * The key associated with moving "left".
 * @var binds::attack
 * The key associated with triggering an attack.
 *
 * @headerfile binds.hpp
 */
struct binds final
{
  cen::key_code up{SDLK_w};
  cen::key_code right{SDLK_d};
  cen::key_code down{SDLK_s};
  cen::key_code left{SDLK_a};
  cen::key_code attack{SDLK_SPACE};
};

}  // namespace wanderer::comp
