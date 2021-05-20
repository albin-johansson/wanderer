#pragma once

#include "core/aliases/map_id.hpp"

namespace wanderer {

/// \brief Emitted when the active map should change.
/// \ingroup events
struct switch_map_event final
{
  map_id map;  ///< The ID associated with new map.
};

}  // namespace wanderer
