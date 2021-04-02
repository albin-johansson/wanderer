#pragma once

#include <entt.hpp>  // registry

#include "serialization.hpp"

namespace wanderer::sys {

void save_registry(const entt::registry& registry, output_archive& archive);

[[nodiscard]] auto restore_registry(input_archive& archive) -> entt::registry;

}  // namespace wanderer::sys
