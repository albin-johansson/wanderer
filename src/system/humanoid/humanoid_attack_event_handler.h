/**
 * This file declares all functions related to handling humanoid attack events.
 *
 * @file humanoid_attack_event_handler.h
 */

#pragma once

#include "begin_attack_event.h"
#include "end_attack_event.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::humanoid {

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.sourceEntity</code> must not have a
 * <code>HumanoidAttack</code> component.
 * @param event the event data associated with the start of the attack.
 */
void on_attack_begin(const BeginAttackEvent& event);

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.sourceEntity</code> must have a
 * <code>HumanoidAttack</code> component.
 * @param event the event data associated with the end of the attack.
 */
void on_attack_end(const EndAttackEvent& event);

}  // namespace wanderer::sys::humanoid
