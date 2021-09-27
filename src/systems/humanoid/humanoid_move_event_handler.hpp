#pragma once

#include "events/humanoid_events.hpp"

namespace wanderer::sys {

/// \name Event handlers
/// \{

/**
 * \brief Handles the event of beginning to move a humanoid.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void on_move_begin(const begin_humanoid_move_event& event);

/**
 * \brief Handles the event of ending the movement of a humanoid.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void on_move_end(const end_humanoid_move_event& event);

/// \} End of event handlers

}  // namespace wanderer::sys
