#pragma once

#include <centurion.hpp>  // color

#include "common/ints.hpp"
#include "core/day_of_week.hpp"

namespace wanderer::ctx {

struct time_of_day final
{
  float hour{};     ///< [0, 24)
  float minute{};   ///< [0, 60)
  float seconds{};  ///< This has no predefined range, it is reset once per in-game day
  int32 week{};     ///< The week index.
  day_of_week day{day_of_week::monday};  ///< The current day.
  cen::color tint;
};

}  // namespace wanderer::ctx
