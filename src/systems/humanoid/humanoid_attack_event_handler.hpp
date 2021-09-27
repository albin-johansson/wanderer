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
void on_attack_begin(const begin_attack_event& event);

/**
 * \brief Handles the event of beginning a humanoid attack sequence.
 *
 * \ingroup systems
 *
 * \param event the associated event data.
 */
void on_attack_end(const end_attack_event& event);

/// \} End of event handlers

}  // namespace wanderer::sys
