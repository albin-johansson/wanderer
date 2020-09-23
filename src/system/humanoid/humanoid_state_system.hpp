#pragma once

#include "begin_attack_event.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::humanoid {

void update_state(entt::registry& registry, entt::dispatcher& dispatcher);

}  // namespace wanderer::sys::humanoid
