#pragma once

#include <entt.hpp>

namespace wanderer::event {

struct interact final
{
  entt::registry* registry{};
  entt::dispatcher* dispatcher{};
};

}  // namespace wanderer::event
