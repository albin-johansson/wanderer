#pragma once

#include <string>  // string

#include <centurion.hpp>  // surface
#include <entt/entt.hpp>  // registry

namespace wanderer {

/// Saves a game in the preferred path, using the specified name
void SaveGame(const std::string& name,
              const entt::registry& shared,
              const cen::surface& snapshot);

void CreateExitSave(const entt::registry& shared, const cen::surface& snapshot);

}  // namespace wanderer
