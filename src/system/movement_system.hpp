#pragma once

#include <entt.hpp>

#include "aabb_tree.hpp"
#include "delta.hpp"
#include "level.hpp"

namespace wanderer::sys {

void update_movement(level& level, delta dt);

}  // namespace wanderer::sys
