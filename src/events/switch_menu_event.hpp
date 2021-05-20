#pragma once

#include "core/menu_id.hpp"

namespace wanderer {

/// \brief Emitted when the active menu should change.
/// \ingroup events
struct switch_menu_event final
{
  menu_id id;  ///< The ID of the new menu.
};

}  // namespace wanderer
