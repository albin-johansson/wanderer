#pragma once

#include <entt/entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer {

void LoadLevels(entt::registry& shared, GraphicsContext& graphics);

}  // namespace wanderer
