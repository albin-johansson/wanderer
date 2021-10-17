#pragma once

#include "events/humanoid_events.hpp"

namespace wanderer::sys {

/// \name Event handlers
/// \{

/**
 * \brief Handles the event of beginning a humanoid attack sequence.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void OnAttackBegin(const BeginAttackEvent& event);

/**
 * \brief Handles the event of beginning a humanoid attack sequence.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void OnAttackEnd(const EndAttackEvent& event);

/// \} End of event handlers

}  // namespace wanderer::sys
