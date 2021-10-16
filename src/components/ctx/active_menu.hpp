#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::ctx {

struct ActiveMenu final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer::ctx
