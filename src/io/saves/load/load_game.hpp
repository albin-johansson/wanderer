#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "core/graphics/graphics_context.hpp"

namespace wanderer {

void load_game(entt::registry& shared,
               graphics_context& graphics,
               const std::string& name);

}  // namespace wanderer
