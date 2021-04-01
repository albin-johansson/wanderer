#pragma once

#include <string>  // string

#include "graphics_context.hpp"
#include "level_manager.hpp"

namespace wanderer {

[[nodiscard]] auto load_game(const std::string& name, graphics_context& graphics)
    -> level_manager;

}
