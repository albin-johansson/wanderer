#pragma once

namespace wanderer {

/// \brief Provides identifiers for all of the possible menu actions.
/// \ingroup core
enum class menu_action
{
  none,
  goto_in_game,
  goto_home,
  goto_settings,
  goto_saves,
  goto_controls,
  quick_save,
  load_game,
  change_save_preview,
  increment_saves_button_group_page,
  decrement_saves_button_group_page,
  quit,
  toggle_fullscreen,
  toggle_integer_scaling,
  toggle_lights
};

}  // namespace wanderer
