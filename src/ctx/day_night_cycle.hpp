#pragma once

#include "ints.hpp"

namespace wanderer::ctx {

struct day_night_cycle final
{
  int hour{13};   ///< [0, 24)
  int minute{0};  ///< [0, 60)
  float tick{};
  u8 opacity{};
};

}  // namespace wanderer::ctx
