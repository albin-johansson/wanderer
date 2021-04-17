#pragma once

#include <centurion.hpp>  // scan_code

#include "core/aliases/ints.hpp"

namespace wanderer::ctx {

/**
 * \struct binds
 *
 * \brief Represents all of the key binds used by the player.
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
  cen::scan_code interact{cen::scancodes::e};
  cen::scan_code inventory{cen::scancodes::i};
};

void serialize(auto& archive, binds& b, u32 version)
{
  archive(b.up, b.right, b.down, b.left, b.attack, b.interact, b.inventory);
}

}  // namespace wanderer::ctx
