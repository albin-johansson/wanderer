#pragma once

#include <string>  // string

#include "core/graphics/graphics_context.hpp"
#include "core/levels/level_manager.hpp"

namespace wanderer {

void load_game(entt::registry& shared,
               graphics_context& graphics,
               const std::string& name);

}  // namespace wanderer
