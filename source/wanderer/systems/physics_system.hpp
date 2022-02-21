#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

void update_physics(entt::registry& registry, float32 dt);

}  // namespace wanderer::sys