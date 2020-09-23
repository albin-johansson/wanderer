#pragma once

#include "component/event/begin_humanoid_move_event.hpp"
#include "component/event/end_humanoid_move_event.hpp"

namespace wanderer::sys::humanoid {

/**
 * @brief Handles the event of beginning the movement of a humanoid.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.entity</code> must not have a <code>HumanoidMove</code>
 * component.
 *
 * @param event the data for the event.
 */
void on_move_begin(const begin_humanoid_move_event& event);

/**
 * @brief Handles the event of ending the movement of a humanoid.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.entity</code> must have a <code>HumanoidMove</code>
 * component.
 *
 * @param event the data for the event.
 */
void on_move_end(const end_humanoid_move_event& event);

}  // namespace wanderer::sys::humanoid
