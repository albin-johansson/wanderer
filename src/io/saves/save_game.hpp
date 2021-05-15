#pragma once

#include <centurion.hpp>  // surface
#include <entt.hpp>       // registry
#include <string>         // string

namespace wanderer {

/// Saves a game in the preferred path, using the specified name
void save_game(const std::string& name,
               const entt::registry& shared,
               const cen::surface& snapshot);

void create_exit_save(const entt::registry& shared, const cen::surface& snapshot);

}  // namespace wanderer
