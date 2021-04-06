#pragma once

namespace wanderer {

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
  quit,
  toggle_fullscreen,
  toggle_integer_scaling,
  toggle_lights
};

}  // namespace wanderer
