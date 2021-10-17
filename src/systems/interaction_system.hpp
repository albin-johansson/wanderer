#pragma once

#include "events/interact_event.hpp"

namespace wanderer::sys {

/// \name Event handlers
/// \{

/**
 * \brief Handles an interaction event.
 *
 * \details This function will process the supplied event and subsequently potentially
 * emit more specific events, depending on the state of the player.
 *
 * \ingroup systems
 *
 * \param event the event data.
 */
void OnInteract(const InteractEvent& event);

/// \} End of event handlers

}  // namespace wanderer::sys
