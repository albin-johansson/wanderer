#pragma once

#include <entt.hpp>

#include "input.h"

namespace wanderer::system::input {

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       entt::entity player,
                       const Input& input);

}  // namespace wanderer::system::input
