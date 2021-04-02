#pragma once

#include <abby.hpp>
#include <entt.hpp>

#include "vector2.hpp"

namespace wanderer {

using aabb_tree = abby::tree<entt::entity, float, float2>;

}
