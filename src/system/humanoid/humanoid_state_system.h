#pragma once

#include "begin_attack_event.h"
#include "types.h"

namespace wanderer::system::humanoid {

void update_state(entt::registry& registry, entt::dispatcher& dispatcher);

}  // namespace wanderer::system::humanoid
