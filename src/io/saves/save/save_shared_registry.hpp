#pragma once

#include <entt.hpp>    // registry
#include <filesystem>  // path

namespace wanderer {

void save_shared_registry(const entt::registry& shared,
                          const std::filesystem::path& path);

}  // namespace wanderer