#pragma once

namespace wanderer {

/// \brief Emitted when the integer scaling option is toggled.
/// \ingroup events
struct integer_scaling_toggled_event final
{
  bool enabled;  ///< The new value of the integer scaling option.
};

}  // namespace wanderer
