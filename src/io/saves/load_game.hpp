#pragma once

#include <string>  // string

#include "core/graphics_context.hpp"
#include "core/levels/level_manager.hpp"

namespace wanderer {

[[nodiscard]] auto load_game(const std::string& name, graphics_context& graphics)
    -> level_manager;

}
