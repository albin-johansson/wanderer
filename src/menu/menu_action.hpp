#pragma once

#include <json.hpp>

namespace wanderer {

enum class menu_action
{
  goto_in_game,
  goto_home,
  goto_settings,
  goto_controls,
  quit,
};

NLOHMANN_JSON_SERIALIZE_ENUM(menu_action,
                             {{menu_action::goto_in_game, "goto_in_game"},
                              {menu_action::goto_home, "goto_home"},
                              {menu_action::goto_settings, "goto_settings"},
                              {menu_action::goto_controls, "goto_controls"},
                              {menu_action::quit, "quit"}});

}  // namespace wanderer
