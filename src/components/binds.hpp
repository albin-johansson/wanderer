#pragma once

#include <centurion.hpp>  // scan_code

#include "wanderer_std.hpp"

namespace wanderer::ctx {

/// \brief Represents all of the key binds used by the player.
struct Binds final
{
  cen::scan_code up{cen::scancodes::w};
  cen::scan_code right{cen::scancodes::d};
  cen::scan_code down{cen::scancodes::s};
  cen::scan_code left{cen::scancodes::a};
  cen::scan_code attack{cen::scancodes::space};
  cen::scan_code interact{cen::scancodes::e};
  cen::scan_code inventory{cen::scancodes::i};
};

}  // namespace wanderer::ctx
