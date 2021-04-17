#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Settings
/// \{

void load_settings(entt::registry& registry);

auto toggle_fullscreen(entt::registry& registry) -> bool;

auto toggle_integer_scaling(entt::registry& registry) -> bool;

auto toggle_simulate_lights(entt::registry& registry) -> bool;

void save_settings_before_exit(const entt::registry& registry);

/// \} End of settings

}  // namespace wanderer::sys
