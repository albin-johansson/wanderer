#pragma once

#include "core/menu_action.hpp"

namespace wanderer {

/// \brief Emitted when a button is pressed.
/// \ingroup events
struct button_pressed_event final
{
  menu_action action;
};

}  // namespace wanderer