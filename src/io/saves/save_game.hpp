#pragma once

#include <string>  // string

#include "core/levels/level_manager.hpp"

namespace wanderer {

/// Saves a game in the preferred path, using the specified name
void save_game(const std::string& name, const level_manager& levels);

}  // namespace wanderer
