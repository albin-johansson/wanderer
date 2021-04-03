#pragma once

#include <centurion.hpp>  // color

#include "ints.hpp"

namespace wanderer::ctx {

struct time_of_day final
{
  float hour{13};    ///< [0, 24)
  float minute{0};   ///< [0, 60)
  float seconds{0};  ///< [0, 60)

  u8 opacity{};
  cen::color color;
};

}  // namespace wanderer::ctx
