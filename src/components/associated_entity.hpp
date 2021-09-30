#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

struct associated_entity final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer::comp
