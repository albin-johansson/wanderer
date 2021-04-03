#pragma once

#include <centurion.hpp>  // color

#include "ints.hpp"

namespace wanderer::ctx {

struct time_of_day final
{
  float hour{};     ///< [0, 24)
  float minute{};   ///< [0, 60)
  float seconds{};  ///< This has no predefined range, it is reset once per in-game day

  u8 opacity{};
  cen::color color;
};

}  // namespace wanderer::ctx
