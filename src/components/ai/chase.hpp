#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

struct chase final
{
  entt::entity target{entt::null};  ///< The entity that will be chased.
  float range{};  ///< The maximum distance at which the target can be chased.
  bool active{};  ///< Whether or not the target is within range.
};

}  // namespace wanderer::comp
