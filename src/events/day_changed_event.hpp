#pragma once

#include "core/day_of_week.hpp"

namespace wanderer {

struct day_changed_event final
{
  day_of_week day{};  ///< The new day.
};

}  // namespace wanderer
