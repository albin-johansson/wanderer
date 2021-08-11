#pragma once

#include <entt.hpp>             // entity
#include <rune/everything.hpp>  // aabb_tree

namespace wanderer {

using aabb_tree = rune::aabb_tree<entt::entity>;

}  // namespace wanderer
