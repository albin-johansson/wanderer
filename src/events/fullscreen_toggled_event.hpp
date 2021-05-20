#pragma once

namespace wanderer {

/// \brief Emitted when the fullscreen option is toggled.
/// \ingroup events
struct fullscreen_toggled_event final
{
  bool enabled;  ///< The new value of the fullscreen option.
};

}  // namespace wanderer
