#pragma once

#include "components/ui/menu.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/menu_action.hpp"
#include "core/menu_id.hpp"

namespace wanderer {

/// \brief Emitted when the active menu should change.
/// \ingroup events
struct switch_menu_event final
{
  menu_id id;  ///< The ID of the new menu.
};

/**
 * \brief Emitted when the active menu *has* changed.
 *
 * \note Do not confuse this event with `switch_menu_event`.
 *
 * \ingroup events
 */
struct menu_switched_event final
{
  comp::menu::entity entity{null<comp::menu>()};  ///< The menu that is now active.
};

/// \brief Emitted when a button is pressed.
/// \ingroup events
struct button_pressed_event final
{
  menu_action action;
};

/// \brief Emitted when the fullscreen option is toggled.
/// \ingroup events
struct fullscreen_toggled_event final
{
  bool enabled;  ///< The new value of the fullscreen option.
};

/// \brief Emitted when the integer scaling option is toggled.
/// \ingroup events
struct integer_scaling_toggled_event final
{
  bool enabled;  ///< The new value of the integer scaling option.
};

}  // namespace wanderer