#pragma once

namespace wanderer {

enum class menu_id
{
  in_game,
  home,
  settings,
  controls
};

NLOHMANN_JSON_SERIALIZE_ENUM(menu_id,
                             {{menu_id::in_game, "in_game"},
                              {menu_id::home, "home"},
                              {menu_id::settings, "settings"},
                              {menu_id::controls, "controls"}})

}  // namespace wanderer
