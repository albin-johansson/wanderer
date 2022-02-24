#pragma once

#include <filesystem>  // path

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::io::tiled {

void parse_tileset(const nlohmann::json& json,
                   const std::filesystem::path& dir,
                   entt::registry& registry,
                   graphics_ctx& graphics);

}  // namespace wanderer::io::tiled