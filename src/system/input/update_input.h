#pragma once

#include <input.h>

#include "types.h"

namespace wanderer {

void update_input(entt::registry& registry,
                  entt::entity player,
                  const Input& input);

}  // namespace wanderer
