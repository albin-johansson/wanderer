#pragma once
#include "wanderer_stdinc.h"

namespace wanderer::system {

void update_viewport(entt::registry& registry,
                     entt::entity viewport,
                     entt::entity player,
                     Delta delta);

}  // namespace wanderer::system
