#pragma once

#include <json.hpp>

namespace wanderer {

enum class key_trigger
{
  on_pressed,
  on_released
};

NLOHMANN_JSON_SERIALIZE_ENUM(key_trigger,
                             {{key_trigger::on_pressed, "on_pressed"},
                              {key_trigger::on_released, "on_released"}});

}  // namespace wanderer
