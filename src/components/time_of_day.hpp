#pragma once

#include <centurion.hpp>  // color

#include "core/day_of_week.hpp"
#include "wanderer_std.hpp"

namespace wanderer::ctx {

struct TimeOfDay final
{
  float hour{};     ///< [0, 24)
  float minute{};   ///< [0, 60)
  float seconds{};  ///< This has no predefined range, it is reset once per in-game day
  int32 week{};     ///< The week index.
  DayOfWeek day{DayOfWeek::Monday};  ///< The current day.
  cen::color tint;
};

}  // namespace wanderer::ctx
