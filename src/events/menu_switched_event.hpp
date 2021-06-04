#pragma once

#include "components/ui/menu.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer {

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

}  // namespace wanderer
