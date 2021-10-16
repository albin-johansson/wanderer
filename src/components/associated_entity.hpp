#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

struct AssociatedEntity final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer::comp
