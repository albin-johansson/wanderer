#pragma once
#include <entt.hpp>

#include "input.h"

namespace wanderer {

void handle_move_input(entt::registry& registry, const Input& input);

}
