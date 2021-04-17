#pragma once

#include "events/begin_attack_event.hpp"
#include "events/end_attack_event.hpp"

namespace wanderer::sys {

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.sourceEntity` must not have a
 * `humanoid_attack` component.
 * \param event the event data associated with the start of the attack.
 */
void on_attack_begin(const event::begin_attack& event);

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * \pre `event.registry` must not be null.
 * \pre `event.sourceEntity` must have a
 * `humanoid_attack` component.
 * \param event the event data associated with the end of the attack.
 */
void on_attack_end(const event::end_attack& event);

}  // namespace wanderer::sys
