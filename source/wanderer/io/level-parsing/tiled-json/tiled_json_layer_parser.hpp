#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "wanderer/common.hpp"

namespace wanderer::io::tiled {

void parse_layer(const nlohmann::json& json,
                 entt::registry& registry,
                 int32 z,
                 const glm::vec2& tileSizeRatio);

}  // namespace wanderer::io::tiled