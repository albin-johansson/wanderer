#pragma once

#include "begin_humanoid_move_event.hpp"
#include "end_humanoid_move_event.hpp"

namespace wanderer::sys::humanoid {

/**
 * \brief Handles the event of beginning the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must not have a `humanoid_move` component.
 *
 * \param event the data for the event.
 */
void on_move_begin(const comp::begin_humanoid_move_event& event);

/**
 * \brief Handles the event of ending the movement of a humanoid.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.entity` must have a `humanoid_move`
 * component.
 *
 * \param event the data for the event.
 */
void on_move_end(const comp::end_humanoid_move_event& event);

}  // namespace wanderer::sys::humanoid
