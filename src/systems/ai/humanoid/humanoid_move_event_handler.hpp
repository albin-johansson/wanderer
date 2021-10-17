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
void OnMoveBegin(const BeginHumanoidMoveEvent& event);

/**
 * \brief Handles the event of ending the movement of a humanoid.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void OnMoveEnd(const EndHumanoidMoveEvent& event);

/// \} End of event handlers

}  // namespace wanderer::sys
