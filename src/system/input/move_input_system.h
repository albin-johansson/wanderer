#pragma once
#include <entt.hpp>

#include "input.h"

namespace wanderer::system::input {

void handle_move_input(entt::registry& registry,
                       entt::entity player,
                       const Input& input);

}  // namespace wanderer::system::input
