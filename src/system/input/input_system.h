#pragma once

#include <input.h>

#include "wanderer_stdinc.h"

namespace wanderer::sys::input {

void update(entt::registry& registry,
            entt::dispatcher& dispatcher,
            entt::entity player,
            const Input& input);

}  // namespace wanderer::sys::input
