#pragma once

#include <abby.hpp>  // tree
#include <entt.hpp>  // entity

#include "core/aliases/float2.hpp"

namespace wanderer {

using aabb_tree = abby::tree<entt::entity, float, float2>;

}
