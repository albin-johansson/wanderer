#pragma once

#include "events/begin_humanoid_move_event.hpp"
#include "events/end_humanoid_move_event.hpp"

namespace wanderer::sys {

/// \name Event handlers
/// \{

/**
 * \brief Handles the event of beginning the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must not have a `humanoid_move` component.
 *
 * \param event the data for the event.
 */
void on_move_begin(const begin_humanoid_move_event& event);

/**
 * \brief Handles the event of ending the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must have a `humanoid_move`
 * component.
 *
 * \param event the data for the event.
 */
void on_move_end(const end_humanoid_move_event& event);

/// \} End of event handlers

}  // namespace wanderer::sys
