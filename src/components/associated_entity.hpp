#pragma once

#include <entt.hpp>  // entity, null

#include "common/ints.hpp"

namespace wanderer::comp {

struct associated_entity final
{
  entt::entity entity{entt::null};
  [[deprecated]] int32 inventory_id{};
};

}  // namespace wanderer::comp
