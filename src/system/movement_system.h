#pragma once
#include <entt.hpp>

#include "wanderer_stdinc.h"

namespace wanderer::system {

void update_movement(entt::registry& registry, Delta delta);

}  // namespace wanderer::system
