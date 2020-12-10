#pragma once

#include <cen/scan_code.hpp>

namespace wanderer::comp {

/**
 * \struct binds
 * \brief Represents all of the key binds used by the player.
 *
 * \var binds::up
 * The key associated with moving "up".
 * \var binds::right
 * The key associated with moving "right".
 * \var binds::down
 * The key associated with moving "down".
 * \var binds::left
 * The key associated with moving "left".
 * \var binds::attack
 * The key associated with triggering an attack.
 *
 * \headerfile binds.hpp
 */
struct binds final
{
  cen::scan_code up{cen::scancodes::w};
  cen::scan_code right{cen::scancodes::d};
  cen::scan_code down{cen::scancodes::s};
  cen::scan_code left{cen::scancodes::a};
  cen::scan_code attack{cen::scancodes::space};
};

}  // namespace wanderer::comp
