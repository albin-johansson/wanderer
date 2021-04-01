#pragma once

#include <entt.hpp>

#include "player.hpp"

namespace wanderer::event {

struct interact final
{
  entt::registry* registry{};
  entt::dispatcher* dispatcher{};
  comp::player::entity player;
};

}  // namespace wanderer::event
