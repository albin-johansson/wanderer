#pragma once

#include <cen/key_code.hpp>

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
  cen::key_code up{cen::keycodes::w};
  cen::key_code right{cen::keycodes::d};
  cen::key_code down{cen::keycodes::s};
  cen::key_code left{cen::keycodes::a};
  cen::key_code attack{cen::keycodes::space};
};

}  // namespace wanderer::comp
