#pragma once

#include <entt.hpp>    // registry, dispatcher
#include <functional>  // reference_wrapper

namespace wanderer {

struct interact_event final
{
  std::reference_wrapper<entt::registry> registry;
  std::reference_wrapper<entt::dispatcher> dispatcher;
};

}  // namespace wanderer
