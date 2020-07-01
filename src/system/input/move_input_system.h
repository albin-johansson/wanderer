#pragma once
#include <entt.hpp>

#include "input.h"

namespace wanderer::sys::input {

void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       entt::entity player,
                       const Input& input);

}  // namespace wanderer::sys::input
