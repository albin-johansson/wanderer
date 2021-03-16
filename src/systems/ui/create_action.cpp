#include "create_action.hpp"

#include <centurion.hpp>

#include "menu_id.hpp"
#include "quit_action.hpp"
#include "switch_menu_action.hpp"

namespace wanderer::sys {

[[nodiscard]] auto create_action(const menu_action menuAction)
    -> std::unique_ptr<action>
{
  switch (menuAction)
  {
    case menu_action::quit:
      return std::make_unique<quit_action>();

    case menu_action::goto_in_game:
      return std::make_unique<switch_menu_action>(menu_id::in_game);

    case menu_action::goto_home:
      return std::make_unique<switch_menu_action>(menu_id::home);

    case menu_action::goto_settings:
      return std::make_unique<switch_menu_action>(menu_id::settings);

    case menu_action::goto_saves:
      return std::make_unique<switch_menu_action>(menu_id::saves);

    case menu_action::goto_controls:
      return std::make_unique<switch_menu_action>(menu_id::controls);

    default:
      cen::log::error("Failed to create action from menu action: %i",
                      menuAction);
      return nullptr;
  }
}

}  // namespace wanderer::sys
