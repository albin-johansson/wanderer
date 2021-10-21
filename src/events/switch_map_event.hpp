#pragma once

#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Emitted when the active map should change.
/// \ingroup events
struct SwitchMapEvent final
{
  MapID map;  ///< The ID associated with new map.
};

}  // namespace wanderer
