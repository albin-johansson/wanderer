#pragma once

#include <entt.hpp>     // entity, null
#include <string_view>  // string_view

namespace wanderer {

struct bond_animation_halfway_event final
{
  std::string_view msg;
  entt::entity entity{entt::null};
};

}  // namespace wanderer
