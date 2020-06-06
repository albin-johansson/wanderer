#pragma once

#include <entt.hpp>

#include "input.h"

namespace wanderer {

void handle_idle_input(entt::registry& registry,
                       entt::entity player,
                       const Input& input);

}
