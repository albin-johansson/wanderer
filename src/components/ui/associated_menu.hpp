#pragma once

#include <entt/entt.hpp>  // entity, null

namespace wanderer {

// TODO replace with associated_entity?
struct AssociatedMenu final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer
