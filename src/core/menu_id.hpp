#pragma once

#include <json.hpp>

namespace wanderer {

enum class menu_id
{
  in_game,
  home,
  settings,
  saves,
  controls
};

NLOHMANN_JSON_SERIALIZE_ENUM(menu_id,
                             {{menu_id::in_game, "in_game"},
                              {menu_id::home, "home"},
                              {menu_id::settings, "settings"},
                              {menu_id::saves, "saves"},
                              {menu_id::controls, "controls"}})

}  // namespace wanderer
