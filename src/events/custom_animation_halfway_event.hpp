#pragma once

#include <entt.hpp>  // entity, null

#include "core/aliases/ints.hpp"

namespace wanderer {

struct custom_animation_halfway_event final
{
  uint32 id{};
  entt::entity entity{entt::null};
};

}  // namespace wanderer
