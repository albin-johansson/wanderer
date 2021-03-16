#pragma once

#include <entt.hpp>

#include "player.hpp"

namespace wanderer::comp {

struct interact_event final
{
  entt::registry* registry{};
  entt::dispatcher* dispatcher{};
  player::entity player;
};

}  // namespace wanderer::comp
