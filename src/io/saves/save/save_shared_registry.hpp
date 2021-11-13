#pragma once

#include <filesystem>  // path

#include <entt/entt.hpp>  // registry

namespace wanderer {

void SaveSharedRegistry(const entt::registry& shared, const std::filesystem::path& path);

}  // namespace wanderer