#pragma once

#include <entt.hpp>  // entity, null

#include "common/ints.hpp"

namespace wanderer {

struct CustomAnimationHalfwayEvent final
{
  uint32 id{};
  entt::entity entity{entt::null};
};

}  // namespace wanderer
