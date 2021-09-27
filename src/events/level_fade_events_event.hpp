#pragma once

#include "common/map_id.hpp"

namespace wanderer {

/// \brief Emitted when a level animation has finished its first "zoom in" phase.
/// \ingroup events
struct level_faded_in_event final
{
  map_id map;         ///< The ID of the map that should be activated.
  float width;        ///< The current width of the left and right "bars".
  float height;       ///< The current height of the upper and lower "bars".
  float x_step_size;  ///< The size of each step in the x-axis.
  float y_step_size;  ///< The size of each step in the y-axis.
};

struct level_faded_out_event final
{};

}  // namespace wanderer
