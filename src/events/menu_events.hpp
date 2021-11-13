#pragma once

#include <entt/entt.hpp>  // entity, null

#include "components/ui/menu.hpp"
#include "core/action.hpp"
#include "core/menu_id.hpp"

namespace wanderer {

/// \brief Emitted when the active menu should change.
/// \ingroup events
struct SwitchMenuEvent final
{
  MenuId id;  ///< The ID of the new menu.
};

/// \brief Emitted when the active menu *has* changed.
/// \note Do not confuse this event with `SwitchMenuEvent`.
/// \ingroup events
struct MenuSwitchedEvent final
{
  entt::entity entity{entt::null};  ///< The menu that is now active.
};

/// \brief Emitted when a button is pressed.
/// \ingroup events
struct ButtonPressedEvent final
{
  Action action;
};

/// \brief Emitted when the fullscreen option is toggled.
/// \ingroup events
struct FullscreenToggledEvent final
{
  bool enabled;  ///< The new value of the fullscreen option.
};

/// \brief Emitted when the integer scaling option is toggled.
/// \ingroup events
struct IntegerScalingToggledEvent final
{
  bool enabled;  ///< The new value of the integer scaling option.
};

}  // namespace wanderer
