#pragma once
#include <entt.hpp>

#include "types.h"

namespace wanderer::system {

void update_movement(entt::registry& registry, float delta);

}  // namespace wanderer::system
