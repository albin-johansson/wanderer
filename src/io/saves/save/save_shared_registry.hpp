#pragma once

#include <filesystem>  // path

#include <entt.hpp>  // registry

namespace wanderer {

void save_shared_registry(const entt::registry& shared,
                          const std::filesystem::path& path);

}  // namespace wanderer