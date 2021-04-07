#pragma once

#include <entt.hpp>    // registry, dispatcher
#include <functional>  // reference_wrapper

namespace wanderer::event {

struct interact final
{
  std::reference_wrapper<entt::registry> registry;
  std::reference_wrapper<entt::dispatcher> dispatcher;
};

}  // namespace wanderer::event
