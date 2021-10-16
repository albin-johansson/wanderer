#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

// TODO replace with associated_entity?
struct AssociatedMenu final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer::comp
