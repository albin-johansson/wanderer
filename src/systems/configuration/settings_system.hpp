#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

void load_settings(entt::registry& registry);

void save_settings_before_exit(const entt::registry& registry);

}
