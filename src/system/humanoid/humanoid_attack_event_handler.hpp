#pragma once

#include "component/begin_attack_event.hpp"
#include "component/end_attack_event.hpp"

namespace wanderer::sys::humanoid {

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.sourceEntity` must not have a
 * `humanoid_attack` component.
 * \param event the event data associated with the start of the attack.
 */
void on_attack_begin(const comp::begin_attack_event& event);

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.sourceEntity` must have a
 * `humanoid_attack` component.
 * \param event the event data associated with the end of the attack.
 */
void on_attack_end(const comp::end_attack_event& event);

}  // namespace wanderer::sys::humanoid
