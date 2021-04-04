#pragma once

#include <abby.hpp>
#include <entt.hpp>

#include "float2.hpp"

namespace wanderer {

using aabb_tree = abby::tree<entt::entity, float, float2>;

}
