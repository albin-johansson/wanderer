#pragma once

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "wanderer/common.hpp"

namespace wanderer::io::tiled {

void parse_layer(const nlohmann::json& json, entt::registry& registry, int32 z);

}  // namespace wanderer::io::tiled