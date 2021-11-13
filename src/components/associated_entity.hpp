#pragma once

#include <entt/entt.hpp>  // entity, null

namespace wanderer {

struct AssociatedEntity final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer
