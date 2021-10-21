#pragma once

#include <entt.hpp>  // entity, null

#include "wanderer_std.hpp"

namespace wanderer {

struct CustomAnimationHalfwayEvent final
{
  uint32 id{};
  entt::entity entity{entt::null};
};

}  // namespace wanderer
