#pragma once

#include <string>  // string

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer {

void load_game(entt::registry& shared,
               GraphicsContext& graphics,
               const std::string& name);

}  // namespace wanderer
