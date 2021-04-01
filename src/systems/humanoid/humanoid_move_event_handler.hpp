#pragma once

#include "begin_humanoid_move.hpp"
#include "end_humanoid_move.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the event of beginning the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must not have a `humanoid_move` component.
 *
 * \param event the data for the event.
 */
void on_move_begin(const event::begin_humanoid_move& event);

/**
 * \brief Handles the event of ending the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must have a `humanoid_move`
 * component.
 *
 * \param event the data for the event.
 */
void on_move_end(const event::end_humanoid_move& event);

}  // namespace wanderer::sys
