#pragma once

#include <string>  // string

#include <centurion.hpp>  // surface
#include <entt/entt.hpp>  // registry

namespace wanderer {

/// Saves a game in the preferred path, using the specified name
void SaveGame(const std::string& name,
              const entt::registry& shared,
              const cen::surface& snapshot);

void create_exit_save(const entt::registry& shared, const cen::surface& snapshot);

}  // namespace wanderer
