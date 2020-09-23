#pragma once

#include "component/event/begin_attack_event.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::humanoid {

void update_state(entt::registry& registry, entt::dispatcher& dispatcher);

}  // namespace wanderer::sys::humanoid
