#pragma once

#include <entt.hpp>  // registry

#include "core/serialization.hpp"

namespace wanderer::sys {

/// \name Saves
/// \{

void save_registry(const entt::registry& registry, output_archive& archive);

[[nodiscard]] auto restore_registry(input_archive& archive) -> entt::registry;

/// \} End of saves

}  // namespace wanderer::sys
