#pragma once

#include "core/day_of_week.hpp"

namespace wanderer {

/// \brief Emitted when the in-game day changes.
/// \ingroup events
struct DayChangedEvent final
{
  DayOfWeek day{};  ///< The new day.
};

}  // namespace wanderer
