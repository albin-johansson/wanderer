#pragma once

#include "events/interact_event.hpp"

namespace wanderer::sys {

/// \name Event handlers
/// \{

void on_interact(const interact_event& event);

/// \} End of event handlers

}
