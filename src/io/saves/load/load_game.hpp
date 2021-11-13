#pragma once

#include <string>  // string

#include <entt/entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer {

void LoadGame(entt::registry& shared, GraphicsContext& graphics, const std::string& name);

}  // namespace wanderer
