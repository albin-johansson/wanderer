#pragma once

#include "core/day_of_week.hpp"

namespace wanderer {

/// \brief Emitted when the in-game day changes.
/// \ingroup events
struct day_changed_event final
{
  day_of_week day{};  ///< The new day.
};

}  // namespace wanderer
